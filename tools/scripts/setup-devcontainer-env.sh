#!/bin/bash
export HOST_IP=$(getent hosts host.docker.internal | awk '{print $1}')
echo "set(JLINK_IP \"$HOST_IP\")" > cmake/jlink_ip.cmake