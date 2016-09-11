# haze
A simple commandline utility to get the current PSI in Singapore, using NEA's API.

I use it to display the current PSI in [`xmobar`](http://projects.haskell.org/xmobar/).

## Usage

At minimum, `haze -k <API_KEY>` will print the reported 3-hour moving average PSI for all of Singapore. You can change the region using `-r`, and calculate the current value using `-c`. 

Here's the output of `haze -h`:
```
haze, gets the latest PSI using the NEA API.
Prints the 3-hour average by default.
Usage: haze [OPTIONS]

OPTIONS:
  -k --api-key=KEY   Use this API key.
  -r --region=REGION The region to report. One of: NRS rCE rEA rNO rSO rWE 
  -c --calculated    Calculate from first principles instead of using the 3-hour average.
  -h --help          Print this and exit.
```

## Compiling

`libcurl` is an external dependency. Your favourite package manager will have some flavour of it. The package `libcurl4-openssl-dev` might help.

Before compiling, edit `config.cpp` to set the default API key if you do not want to pass one each time you run the program. The first time you run `make`, some dependencies will be downloaded automatically.

Targets: 

  - `make`, `make all` builds `haze`,
  - `make test` builds and runs tests, and --
  - `make install` builds and copies the built binary to `/usr/local/bin/`.

