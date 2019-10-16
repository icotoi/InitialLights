from __future__ import print_function
import logging

import grpc

import initiallights_pb2
import initiallights_pb2_grpc


def run():
    # NOTE(gRPC Python Team): .close() is possible on a channel and should be
    # used in circumstances in which the with statement does not fit the needs
    # of the code.
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = initiallights_pb2_grpc.UserStub(channel)
        response = stub.Login(initiallights_pb2.LoginRequest(email='foo', password='bar'))
        print('Login user: foo/bar -> ' + repr(response.success) + ' | ' + response.message + ' | ' + response.email)
        response = stub.Login(initiallights_pb2.LoginRequest(email='xxx', password='xxx'))
        print('Login user: foo/bar -> ' + repr(response.success) + ' | ' + response.message + ' | ' + response.email)


if __name__ == '__main__':
    logging.basicConfig()
    run()
