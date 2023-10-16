```                                      
                                   @@@@  @@@@             @@@@ @@@@           
                                   @@@@  @@@@             @@@@ @@@@           
                                                                                
           @@@@  @@@@,  &@@@@&     @@@@    @@@@ &@@@@     @@@@                 
           @@@@@@@@@@@@@@@@@@@@,   @@@@    @@@@@@@@@@@@   @@@@                 
           @@@@    @@@@    @@@@@   @@@@    @@@@    @@@@   @@@@                 
           @@@@    @@@@    (@@@@   @@@@    @@@@    @@@@   @@@@                 
           @@@@    @@@@    (@@@@   @@@@    @@@@    @@@@   @@@@                 
           @@@@    @@@@    (@@@@   @@@@    @@@@    @@@@   @@@@                 
           @@@@    @@@@    (@@@@   @@@@    @@@@    @@@@   @@@@                 
           @@@@    @@@@    (@@@@   @@@@    @@@@    @@@@   @@@@                 
           @@@@    @@@@    (@@@@   @@@@    @@@@    @@@@   @@@@       
                     
           @@@@@@@@@   @@@@@@@@@           @@@@@@@ @@@@                       
           @@@@@@@@@   @@@@@@@@@           @@@@@@@ @@@@                       
                                                                                
                                   @@@@    @@@@  @@@@@@@ @@@ @@@@@@@@           
            @@@@     @@@@@@@ @@@@  @@@@    @@@@  @@@@@@@ @@@ @@@@@@@@           
            @@@@     @@@@@@@ @@@@  @@@@    @@@@                                 
            @@@@                   @@@@    @@@@                                 
          @@@@@@@@@  @@@@@@@@@@    @@@@    @@@@    @@@@                         
            @@@@    @@@@    @@@@   @@@@    @@@@  #@@@%                          
            @@@@            @@@@   @@@@    @@@@ @@@@                            
            @@@@     @@@@@@@@@@@   @@@@    @@@@@@@@@                            
            @@@@    @@@@@   @@@@   @@@@    @@@@@@@@@@                           
            @@@@    @@@@    @@@@   @@@@    @@@@   @@@@                          
            @@@@@@  @@@@@  @@@@@   @@@@@@  @@@@    @@@@\                        
             %@@@@   @@@@@@ @@@@    @@@@@  @@@@     @@@@@    
                  
          @@@@@@@@                @@@ @@@@@@@ @@@ @@@                              
          @@@@@@@@                @@@ @@@@@@@ @@@ @@@
 
 whoAmI(campus=42barcelona, login=mporras-, mail=manuel.porras.ojeda@gmail.com)
 Feel free to write!    
```

# Mini-Talk

## Description
Mini-Talk is a communication application that enables message transfers between a client and a server using UNIX signals. This system leverages the robustness of signal communication, allowing the client to send messages to the server, which the server then processes and outputs.

### Grade: 125%.
I didn't include ft_printf cuz I gotta check its Makefile to avoid some errors.
### Tips:

- Play with usleep time. It's not a super reliable function, and that behaviour can be critical. 
- To debug or try a small version of mini-talk, avoid the use of printf, or you can be trapped with estranges results or no result at all. Why? this is a good moment to read about buffered and unbuffered functions:

#### Buffered vs. Unbuffered I/O:

Input/Output (I/O) operations can be time-consuming, especially when dealing with disk or network I/O. For this reason, many systems and programming languages implement what's known as buffered I/O.

#### Buffered I/O:

When you write data using functions that utilize buffered I/O, the data isn't immediately written to the final destination (like a terminal or file). Instead, it's temporarily stored in a buffer. When this buffer fills up, or under certain conditions (like encountering a newline character in some systems), the data is "flushed" from the buffer and written to its final destination.

`printf()` is an example of a function that employs buffered I/O. By default, `printf()` stores its output in a buffer. If `printf()` is used to write to the terminal (stdout), it will typically flush this buffer and write its content to the terminal upon encountering a newline character (unless this default behavior is altered).

#### Unbuffered I/O:

In unbuffered I/O, data is written directly to the final destination without being temporarily stored in a buffer.

`write()` is an example of a function that uses unbuffered I/O. When you use `write()`, the data is immediately written, without waiting for a buffer to fill up or encountering a specific character.

#### Comparison between `printf` and `write`:

Consider the following code:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Hello without newline");
    write(STDOUT_FILENO, "Hello with newline\n", 18);
    return 0;
}
```

If you run this code, you might only see "Hello with newline" on the terminal. This is because the "Hello without newline" from `printf` is waiting in the buffer and hasn't been flushed to the terminal since there's no newline character. However, "Hello with newline" from `write` displays immediately because `write` doesn't use buffering.

If you change the `printf` to `printf("Hello without newline\n");`, both messages will display since the newline character will cause `printf` to flush its buffer.

It's important to be aware of these differences when writing programs, especially when mixing different I/O methods within one program.


## Bitwise Process
Each character in a message is represented by 8 bits in the computer memory. The client breaks down the character into these individual bits through bitwise operations. Specifically, the client performs a bitwise shift and bitwise AND operations to determine the value of each bit in a character. Depending on the value (0 or 1), a corresponding signal (`SIGUSR1` for '1' and `SIGUSR2` for '0') is sent to the server.

On the server side, the received signals are assembled back into a character using bitwise operations. The server keeps track of the received signals for a character, and once all 8 bits are received, it consolidates them into the original character, which is then displayed.

## Workflow

```
  Client                        Server
    |                              |
    |  1. Converts char to binary  |
    |    and sends via signals     |
    | ---------------------------> |
    |                              |
    |  2. Server receives signal   |
    |     and processes it         |
    |                              |
    |  3. Server translates signal |
    |     back to character        |
    |                              |
    |  4. Server outputs message   |
    |     and acknowledges receipt |
    | <--------------------------- |
    |                              |
    |  5. Client continues to send |
    |     next character or ends   |
    |                              |
```

## How to Use

### Server
1. Run the server using the command:
   ```
   ./server
   ```
2. The server will display its PID, which will be used by the client to send messages.

### Client
1. To send a message to the server, use the command:
   ```
   ./client [PID-server] "message to send"
   ```
   Replace `[PID-server]` with the PID displayed by the server.

2. The client will convert the message to its binary representation and send it to the server using signals.

3. The server will acknowledge the receipt of the message and display it.

## Signals and their Management

Signals are a limited form of inter-process communication in Unix. They are asynchronous notifications sent to a process or to a specific thread within a process in order to notify it to perform some action such as handling an event or terminating.

In Mini-Talk, we specifically use two signals, `SIGUSR1` and `SIGUSR2`. Each character in the message from the client is translated into its binary form. A `SIGUSR1` indicates a '1' and `SIGUSR2` indicates a '0'. This binary stream of signals is sent sequentially for each character in the message.

The server is set up to listen for these signals. When a signal is received, it reconstructs the binary back into the character form. Once the end of a message (null character) is detected, the server acknowledges the complete reception of the message.

To ensure the integrity of the process, our server employs a custom handler (`ft_handler`) using the `sigaction` system call. This allows us to have more control over the received signals, including accessing the sender's PID. The client sends each bit of the character and waits briefly to ensure the server has time to process it before sending the next.

# Bonus Server Features

#### Real-time Acknowledgment
The bonus segment of the server ensures that for every byte received, an acknowledgment signal is sent back to the client. This creates a two-way communication stream where the server not only processes the messages but also sends feedback in real-time for every byte it processes.

#### How It Works
1. The server listens for incoming signals from the client.
2. As it receives each byte (8 bits), it processes and displays the corresponding character.
3. After processing each byte, the server sends an acknowledgment signal back to the client using `SIGUSR1`.
4. If the byte processed is a null character, indicating the end of a message, the server sends an acknowledgment using `SIGUSR2` and then displays the total number of bits processed for that message.

#### Workflow:

```
  Client                        Server
    |                              |
    |  1. Converts char to binary  |
    |    and sends via signals     |
    | ---------------------------> |
    |                              |
    |  2. Server receives signal   |
    |     and processes it         |
    |                              |
    |  3. Server translates signal |
    |     back to character        |
    |                              |
    |  4. Server sends             |
    |     acknowledgment via       |
    |     SIGUSR1 for byte         |
    | <--------------------------- |
    |                              |
    |  5. If end of message,       |
    |     server sends             |
    |     acknowledgment via       |
    |     SIGUSR2 and resets       |
    |                              |
    |  6. Client continues to send |
    |     next character or ends   |
    |                              |
```

#### Enhanced Error Handling
In addition to the client's advanced error handling, the server is also fortified to handle signal sending errors. If the server faces any issue in sending acknowledgment signals, it immediately displays an error message and terminates gracefully.

## Generating Documentation with Doxygen

To generate detailed, and more friendly documentation for this project, follow the steps outlined below:

### 1. Install Doxygen:

If you haven't already installed Doxygen, you can do so using your system's package manager.

* Debian/Ubuntu-based systems:

```bash
sudo apt-get install doxygen
```

* On macOS:

```bash
brew install doxygen
```

### 2. Generate the Documentation:

From the root directory of the project, where the `Doxyfile` is located, run:

```bash
doxygen Doxyfile
```

### 3. View the Documentation:

Once Doxygen completes the documentation generation, you can view it by opening the `html/index.html` file in your preferred web browser:

```bash
open docs/html/index.html   # On macOS
xdg-open docs/html/index.html   # On Linux systems
```

