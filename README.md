Original document are [moved](README_old.md).
`master` branch of this fork is copied version from original's `develop` branch.

# How to build Docker image

Run `make docker-build`.

# How to run 

## Show help

`docker run ldltools/scxmlrun-dev --help`

## Run an SCXML

`docker run ldltools/scxmlrun-dev -v <directory where the scxml is located>:/root <arguments to scxmlrun>`
