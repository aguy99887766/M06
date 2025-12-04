#!/bin/bash

while true; do

    read -p "Client: " user_input
    echo $user_input | nc localhost 8080

done
