# first stage base image
FROM ubuntu:latest

# Run make file to build the project
RUN apt-get -y update && apt-get install -y

# Run make file to build the project
RUN apt-get -y install make
RUN apt-get -y install clang


# copy project
COPY . /usr/src

# place for makefile
WORKDIR /usr/src

# Run make file to build the project
RUN make

# run the program
CMD ["./client_main"]
