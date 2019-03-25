Original document are [moved](README_old.md).
`master` branch of this fork is copied version from original's `develop` branch.

# How to build Docker image

Run `make docker-build`.

# How to run 

## Show help

Running `docker run ldltools/scxmlrun-dev --help` shows:

```
scxmlrun v0.12.0rc
usage: scxmlrun <option>* <scxmlfile>? <infile>?
options
  -m <scxmlfile>        read scxml from <scxmlfile>

  -i <infile>           read input events from <infile>
  -o <outfile>          write output events to <outfile>
  --trace <tracefile>   write trace to <tracefile>

  --mqtt                assume MQTT-based I/O by default
  --broker <host>       connect to <host> as the MQTT broker
  --sub <topic>         subscribe to <topic> for input events
  --pub <topic>         publish output events to <topic> by default
  --trace-pub <topic>   publish trace to <topic>

  -h, --help            display this message
  -v, --verbose         become verbose
  -q, --silent          stay quiet
  -V, --version         show version info
```

## Run an SCXML

`docker run ldltools/scxmlrun-dev -v <directory where the scxml is located>:/root <arguments to scxmlrun>`
