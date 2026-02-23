# minitalk

A small data exchange program using UNIX signals, built for [42](https://42.fr).

## How it works

The **server** displays its PID and waits for incoming messages.
The **client** takes the server PID and a string, then sends it character by character using only two signals:

- `SIGUSR1` → bit `0`
- `SIGUSR2` → bit `1`

Each character is encoded as 8 bits (LSB first). The server reconstructs the characters and prints the message once the null terminator is received.

## Build

```
make        # compile client and server
make clean  # remove object files
make fclean # remove everything
make re     # full rebuild
```

## Usage

```
# Terminal 1
./server
PID: 12345

# Terminal 2
./client 12345 "Hello World"
minitalk: message sent with success!
```

## Tests

```
python3 test.py
```

Runs 48 tests covering error handling, special characters, binary edge values, stress (up to 5000 chars), and server persistence.
