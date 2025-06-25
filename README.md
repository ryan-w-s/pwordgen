# pwordgen

A simple password generator application.

## Installation

This project uses Conan 2.x and Meson for building.

1.  **Install dependencies and generate build files:**
    ```bash
    conan install .
    ```

2.  **Build the application:**
    ```bash
    conan build .
    ```

This will create the `pwordgen` executable inside the `build/` directory.

## Usage

To run the application, execute the binary from the project root:

```bash
./build/pwordgen
```

To create a distributable Conan package, you can run:
```bash
conan create .
``` 