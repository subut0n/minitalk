#!/usr/bin/env python3
"""minitalk test suite with edge cases."""

import subprocess
import time
import signal
import os
import sys

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[1;33m"
CYAN = "\033[0;36m"
NC = "\033[0m"

PASS = 0
FAIL = 0
TOTAL = 0
server_proc = None


def start_server():
    global server_proc
    stop_server()
    server_proc = subprocess.Popen(
        ["./server"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    time.sleep(0.3)
    if server_proc.poll() is not None:
        print(f"{RED}Server failed to start{NC}")
        return None
    pid_line = server_proc.stdout.readline().decode().strip()
    pid = pid_line.replace("PID: ", "")
    print(f"  Server started with PID {pid}")
    return pid


def stop_server():
    global server_proc
    if server_proc and server_proc.poll() is None:
        server_proc.send_signal(signal.SIGTERM)
        try:
            server_proc.wait(timeout=2)
        except subprocess.TimeoutExpired:
            server_proc.kill()
    server_proc = None


def read_server_line(timeout=5):
    """Read one line from server stdout with timeout."""
    if not server_proc:
        return None
    import select
    ready, _, _ = select.select([server_proc.stdout], [], [], timeout)
    if ready:
        line = server_proc.stdout.readline().decode()
        if line.endswith("\n"):
            line = line[:-1]
        return line
    return None


def run_test(name, message, expected, timeout=10):
    global TOTAL, PASS, FAIL
    TOTAL += 1
    label = f"[{TOTAL:02d}] {name}"
    print(f"{CYAN}{label:<50}{NC}", end="", flush=True)

    pid = str(server_proc.pid)
    try:
        result = subprocess.run(
            ["./client", pid, message],
            capture_output=True,
            timeout=timeout,
        )
        client_out = (result.stdout + result.stderr).decode().strip()
    except subprocess.TimeoutExpired:
        print(f" {RED}TIMEOUT{NC}")
        FAIL += 1
        return False

    server_out = read_server_line(timeout=3)

    if server_out == expected and "success" in client_out:
        print(f" {GREEN}OK{NC}")
        PASS += 1
        return True
    else:
        print(f" {RED}FAIL{NC}")
        FAIL += 1
        print(f"    expected: {repr(expected)}")
        print(f"    server:   {repr(server_out)}")
        print(f"    client:   {repr(client_out)}")
        return False


def run_error_test(name, args):
    global TOTAL, PASS, FAIL
    TOTAL += 1
    label = f"[{TOTAL:02d}] {name}"
    print(f"{CYAN}{label:<50}{NC}", end="", flush=True)

    try:
        result = subprocess.run(
            ["./client"] + args,
            capture_output=True,
            timeout=5,
        )
        combined = (result.stdout + result.stderr).decode().strip()
        if result.returncode != 0:
            print(f" {GREEN}OK{NC} (exit {result.returncode}: {combined})")
            PASS += 1
            return True
        else:
            print(f" {RED}FAIL{NC} (expected error, got exit 0)")
            FAIL += 1
            return False
    except subprocess.TimeoutExpired:
        print(f" {RED}TIMEOUT{NC}")
        FAIL += 1
        return False


def section(title):
    print(f"\n{YELLOW}--- {title} ---{NC}")


def main():
    global PASS, FAIL, TOTAL

    print(f"\n{YELLOW}========== MINITALK TEST SUITE =========={NC}\n")

    # --- Build ---
    print(f"{YELLOW}[BUILD]{NC} Compiling...")
    r = subprocess.run(["make", "re"], capture_output=True)
    if r.returncode != 0:
        print(f"{RED}Build failed!{NC}")
        print(r.stderr.decode())
        sys.exit(1)
    print(f"{GREEN}Build OK{NC}")

    # --- Signal check ---
    print(f"\n{YELLOW}[SIGNAL CHECK]{NC} Verifying only SIGUSR1/SIGUSR2...")
    bad = subprocess.run(
        ["grep", "-rn",
         r"SIGINT\|SIGTERM\|SIGKILL\|SIGSTOP\|SIGPIPE\|SIGALRM\|SIGHUP\|SIGQUIT",
         "srcs/"],
        capture_output=True,
    )
    if bad.returncode != 0:
        print(f"{GREEN}Only SIGUSR1 and SIGUSR2 used{NC}")
    else:
        print(f"{RED}WARNING: Other signals found:{NC}")
        print(bad.stdout.decode())

    # ==========================================================
    section("Error handling (client)")
    # ==========================================================

    run_error_test("No arguments", [])
    run_error_test("One argument only", ["12345"])
    run_error_test("Too many arguments", ["12345", "hello", "extra"])
    run_error_test("Invalid PID (0)", ["0", "hello"])
    run_error_test("Invalid PID (negative)", ["-1", "hello"])
    run_error_test("Invalid PID (letters)", ["abc", "hello"])
    run_error_test("Invalid PID (dead process)", ["99999", "hello"])

    # ==========================================================
    section("Server error handling")
    # ==========================================================

    TOTAL_before = TOTAL
    TOTAL += 1
    label = f"[{TOTAL:02d}] Server rejects arguments"
    print(f"{CYAN}{label:<50}{NC}", end="", flush=True)
    r = subprocess.run(["./server", "foo"], capture_output=True, timeout=3)
    if r.returncode != 0:
        print(f" {GREEN}OK{NC}")
        PASS += 1
    else:
        print(f" {RED}FAIL{NC}")
        FAIL += 1

    # ==========================================================
    section("Basic messages")
    # ==========================================================

    srv_pid = start_server()
    if not srv_pid:
        sys.exit(1)

    run_test("Simple word", "Hello", "Hello")
    run_test("Two words", "Hello World", "Hello World")
    run_test("Single character", "A", "A")
    run_test("Single space", " ", " ")
    run_test("Empty string", "", "")
    run_test("Numbers", "1234567890", "1234567890")

    # ==========================================================
    section("Special characters")
    # ==========================================================

    run_test("Punctuation", "!@#$%^&*()", "!@#$%^&*()")
    run_test("Quotes and slashes", "\"hello\" 'world' /path\\", "\"hello\" 'world' /path\\")
    run_test("Tab characters", "col1\tcol2\tcol3", "col1\tcol2\tcol3")
    run_test("Mixed special chars", "a!b@c#d$e%f^g&h", "a!b@c#d$e%f^g&h")
    run_test("Tilde and braces", "~{[test]}", "~{[test]}")
    run_test("Semicolons and pipes", "cmd1;cmd2|cmd3", "cmd1;cmd2|cmd3")
    run_test("Backslash only", "\\", "\\")
    run_test("Equals and plus", "a=1+2", "a=1+2")

    # ==========================================================
    section("Stress tests")
    # ==========================================================

    run_test("100 chars", "A" * 100, "A" * 100, timeout=10)
    run_test("500 chars", "B" * 500, "B" * 500, timeout=20)
    run_test("1000 chars", "C" * 1000, "C" * 1000, timeout=40)

    # Restart server for the big one
    stop_server()
    srv_pid = start_server()

    run_test("5000 chars (long)", "D" * 5000, "D" * 5000, timeout=120)

    # ==========================================================
    section("Consecutive messages (server persistence)")
    # ==========================================================

    stop_server()
    srv_pid = start_server()

    run_test("Msg 1/5", "First", "First")
    run_test("Msg 2/5", "Second", "Second")
    run_test("Msg 3/5", "Third", "Third")
    run_test("Msg 4/5", "Fourth", "Fourth")
    run_test("Msg 5/5", "Fifth", "Fifth")

    # ==========================================================
    section("Boundary / binary values")
    # ==========================================================

    # All printable ASCII (32-126)
    all_printable = "".join(chr(i) for i in range(32, 127))
    run_test("All printable ASCII (32-126)", all_printable, all_printable, timeout=30)

    run_test("DEL char (127)", "\x7f", "\x7f")
    run_test("Repeated same char", "AAAAAAAAAA", "AAAAAAAAAA")
    run_test("Alternating bits (U=0x55)", "UUUUUUUUUU", "UUUUUUUUUU")
    run_test("All bits 0 pattern (spaces)", "          ", "          ")
    run_test("Char 0x01", "\x01", "\x01")
    run_test("Char 0x7F", "\x7f", "\x7f")

    # High bytes (extended ASCII)
    run_test("Char 0x80", "\x80", "\x80")
    run_test("Char 0xFE", "\xfe", "\xfe")
    run_test("Char 0xFF", "\xff", "\xff")

    # Mix of low and high byte values
    mixed_binary = "\x01\x02\x7f\x80\xfe\xff"
    run_test("Mixed binary values", mixed_binary, mixed_binary)

    # ==========================================================
    section("Pattern-specific tests")
    # ==========================================================

    # These test specific bit patterns that could expose shifting bugs
    # Note: \x00 can't be passed as CLI arg (C string terminator)
    run_test("Char 0x01 (00000001)", "\x01" * 5, "\x01" * 5)
    run_test("Char 0x80 (10000000)", "\x80" * 5, "\x80" * 5)
    run_test("Char 0xAA (10101010)", "\xaa" * 5, "\xaa" * 5)
    run_test("Char 0x55 (01010101)", "\x55" * 5, "\x55" * 5)

    # Long message with varied content
    varied = "".join(chr(((i * 7 + 13) % 126) + 1) for i in range(200))
    run_test("200 varied chars", varied, varied, timeout=15)

    # ==========================================================
    section("Server still alive after everything")
    # ==========================================================

    run_test("Final check", "still alive!", "still alive!")

    stop_server()

    # ==========================================================
    # Results
    # ==========================================================
    print(f"\n{YELLOW}========== RESULTS =========={NC}")
    print(f"Total: {TOTAL}")
    print(f"Pass:  {GREEN}{PASS}{NC}")
    print(f"Fail:  {RED}{FAIL}{NC}")
    print()

    if FAIL == 0:
        print(f"{GREEN}All tests passed!{NC}")
    else:
        print(f"{RED}{FAIL} test(s) failed.{NC}")

    sys.exit(0 if FAIL == 0 else 1)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print(f"\n{YELLOW}Interrupted{NC}")
        stop_server()
        sys.exit(130)
    finally:
        stop_server()
