Implementation of test interview task: mobile billing system. To build:
```
mkdir build
cd build
cmake ../
make
```
All binaries will then be present in build/bin directory. You can execute main
application using sample configuration and input files that are provided in
root directory like this (assuming you start in the build subdirectory):

`bin/MainApplication -c ../sample_controller_config.cfg -r ../sample_call_records.almost.csv -a ../sample_accounts_info_records.almost.csv -o output_call_prices.txt`
