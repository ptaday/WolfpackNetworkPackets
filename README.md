# WolfPack Network Protocol Implementation in C

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## Description

This project involves the implementation of a fictional network protocol called WolfPack. WolfPack network packets contain various fields and a data payload, similar to a real network packet format. The protocol handles aspects such as addressing, port numbers, fragmentation, and more. This implementation works with big endian ordering, which differs from common computer architectures like Intel and Apple M1/M2. The provided functions deal with converting between little endian and big endian when reading and writing packets.

## Features

- Implementation of the WolfPack network protocol based on a fictional specification.
- Handling of network packets with fields such as Source Address, Destination Address, Port numbers, Fragmentation Offset, Flags, Total Length, and Checksum.
- Functions to print packet fields and payload, compute packet checksum, reconstruct messages from packets, and packetize messages.
- Error handling for corrupted packets and memory allocation.

## Prerequisites

- Basic understanding of the C programming language.
- Familiarity with network protocols and data structures.

## Installation

1. Clone this repository to your local machine.
2. Open the project in your preferred C development environment (e.g., VS Code).
3. Compile and build the project using the provided build commands.

## Usage

To use this implementation of the WolfPack network protocol:

1. Include the necessary headers from the `include` directory.
2. Implement the provided functions in your code to work with WolfPack packets and messages.
3. Utilize the functions to print packet fields and payload, compute checksums, reconstruct messages, and packetize messages.

Ensure that you handle error cases, follow the guidelines outlined in the assignment description, and use the functions as intended.

## Contributing

Contributions to this project are welcome. If you find any issues or improvements, please submit a pull request. Follow the provided guidelines for contributing and ensure that your code adheres to the coding standards.

## Testing 

- The provided unit tests (written using Criterion) help verify the correctness of your implementation.
- Test your code with both computational tests and Valgrind tests for memory errors.
- Use the provided make commands to compile, test, and check test coverage.

git add .
git commit -am " any message here"
git push origin

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For any inquiries or feedback, please contact:
- Pushkar Taday
- Email: pmtaday@gmail.com
- GitHub: ptaday


