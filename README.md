# 🌌 ip-nose: A Matrix-Themed IP Geolocation CLI Tool

![ip-nose](https://img.shields.io/badge/ip--nose-v1.0.0-brightgreen)

Welcome to **ip-nose**, a command-line interface (CLI) tool designed for IP geolocation enthusiasts and developers who appreciate a cyberpunk aesthetic. This project combines the elegance of Matrix themes with practical functionality, making it a unique addition to your toolkit.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)
- [Links](#links)

## Features

- **IP Detection**: Quickly find the geolocation of any IP address.
- **Search History**: Keep track of your recent searches for easy access.
- **Colorized Interface**: Enjoy a vibrant command-line experience that enhances usability.
- **Customizable Configuration**: Tailor the tool to meet your specific needs.

Whether you are a developer looking to integrate IP geolocation into your projects or a network enthusiast wanting to explore the digital world, **ip-nose** offers a powerful and visually appealing solution.

## Installation

To get started with **ip-nose**, you need to compile and install it. Follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/ZORO2304/ip-nose.git
   cd ip-nose
   ```

2. Compile the project using `make`:
   ```bash
   make
   ```

3. After compilation, you can find the executable in the `bin` directory.

4. To install the tool, you can move the executable to a directory in your PATH, such as `/usr/local/bin`:
   ```bash
   sudo mv bin/ip-nose /usr/local/bin/
   ```

5. Now, you can run **ip-nose** from anywhere in your terminal.

For the latest releases, visit the [Releases section](https://github.com/ZORO2304/ip-nose/releases) to download and execute the latest version.

## Usage

Using **ip-nose** is straightforward. Open your terminal and run the following command:

```bash
ip-nose [options] [IP address]
```

### Options

- `-h`, `--help`: Show help information.
- `-v`, `--version`: Display the current version of **ip-nose**.
- `-s`, `--search`: Search for a specific IP address.

### Example

To find the geolocation of an IP address, simply run:

```bash
ip-nose -s 8.8.8.8
```

This command will return the location details, including country, city, and ISP information.

## Configuration

You can customize **ip-nose** to suit your preferences. The configuration file is located in your home directory under `.ip-nose/config.json`. Here’s how to modify it:

1. Open the configuration file in your favorite text editor:
   ```bash
   nano ~/.ip-nose/config.json
   ```

2. Adjust settings such as:
   - Default output format (JSON, plain text)
   - Enable or disable colorized output
   - Set your preferred API for IP geolocation

3. Save the changes and restart **ip-nose** for them to take effect.

## Contributing

We welcome contributions to **ip-nose**! If you have ideas for new features, bug fixes, or improvements, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or fix:
   ```bash
   git checkout -b feature-name
   ```
3. Make your changes and commit them:
   ```bash
   git commit -m "Add feature"
   ```
4. Push your changes to your fork:
   ```bash
   git push origin feature-name
   ```
5. Create a pull request on GitHub.

Your contributions help make **ip-nose** better for everyone.

## License

**ip-nose** is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Links

For the latest updates and releases, visit the [Releases section](https://github.com/ZORO2304/ip-nose/releases).

Explore the world of IP geolocation with **ip-nose** and enjoy a unique, stylish experience in your command line. Happy coding!