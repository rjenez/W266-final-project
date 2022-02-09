#!/bin/sh
# Get the homework plagiarism dataset
#

USER=$IEEE_USER
PASS=$IEEE_PASSWORD

wget --user $USER --password $PASS https://ieee-dataport.s3.amazonaws.com/open/26185/plagiarism-dataset.tar.gz?response-content-disposition=attachment%3B%20filename%3D%22plagiarism-dataset.tar.gz%22&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAJOHYI4KJCE6Q7MIQ%2F20220209%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20220209T014916Z&X-Amz-SignedHeaders=Host&X-Amz-Expires=3600&X-Amz-Signature=7fc3df71cd12da4bd9ddd3f9ab6d946b9d7c11aeef8d4075a4b43273bc0925e9
