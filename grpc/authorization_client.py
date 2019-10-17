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
        def formatSuccess(value):
            return 'ok' if value else 'failed'

        stub = initiallights_pb2_grpc.AuthorizationStub(channel)

        response = stub.Login(initiallights_pb2.LoginRequest(email='foo', password='bar'))
        print('Login foo: {}, reason: {}'.format(formatSuccess(response.success), response.message))
        response = stub.Login(initiallights_pb2.LoginRequest(email='xxx', password='xxx'))
        print('Login xxx: {}, response email: {}, token: {}'.format(formatSuccess(response.success), response.email, response.token))
        response = stub.Login(initiallights_pb2.LoginRequest(email='xxx', password='xxx'))
        print('Login xxx: {}, response email: {}, token: {}'.format(formatSuccess(response.success), response.email, response.token))
        response = stub.Login(initiallights_pb2.LoginRequest(email='xxx', password='xxx'))
        print('Login xxx: {}, response email: {}, token: {}'.format(formatSuccess(response.success), response.email, response.token))

        token = response.token # save for logout bellow

        response = stub.RegisterNewUser(initiallights_pb2.RegisterNewUserRequest(email='xxx', password='123', fullName='Xxx Yyy'))
        print('Registering user xxx: {}, reason: {}'.format(formatSuccess(response.success), response.message))
        response = stub.RegisterNewUser(initiallights_pb2.RegisterNewUserRequest(email='abc', password='123', fullName='Aaa Bbb'))
        print('Registering user abc: {}'.format(formatSuccess(response.success)))

        response = stub.ResetPassword(initiallights_pb2.ResetPasswordRequest(email='xxx'))
        response = stub.ResetPassword(initiallights_pb2.ResetPasswordRequest(email='abc'))

        response = stub.Logout(initiallights_pb2.LogoutRequest(email='abc', token='abc'))
        response = stub.Logout(initiallights_pb2.LogoutRequest(email='xxx', token=token)) # logout with valid token - token will be removed
        response = stub.Logout(initiallights_pb2.LogoutRequest(email='xxx', token='')) # logout with empty token - remove all login tokens

if __name__ == '__main__':
    logging.basicConfig()
    run()
