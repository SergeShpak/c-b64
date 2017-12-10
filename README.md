# C-B64

B64 encoder/decoder implemented in C.

An example of usage is given in [example folder](example). The code is
documented for [Doxygen](http://www.stack.nl/~dimitri/doxygen/).

## Running the tests

Tests are written with the use of [Google Testing framework](https://github.com/google/googletest). You need to perform the following steps to run them:

1. Suppose the b64-c sources are in *{B64-C}* directory. Get the Google Test sources:

```
git clone https://github.com/google/googletest.git
```

You should save the *googletest* folder in *{B-64C}/googletest/*, to compile the tests without touching the corresponding Makefile. However, if you want to use another location for the *GTests* sources, change the variable **GOOGLE_TEST_DIR** in the tests [Makefile](tests/Makefile) to the *GTests* sources path.

2. Suppose you saved the sources in *{GTest}* folder. Compile the *gtest* lib as follows:

```
mkdir -p {GTest}/build/ && cd {GTest}/build/ && cmake .. && make
```

3. Go to the *{B-64C}/tests* and run *make*:

```
cd {B-64C}/tests && make
```

4. Execute the tests:

```
{B-64C}/tests/bin/tests
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE)
file for details.
