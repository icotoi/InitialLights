from concurrent import futures
import logging

import grpc
import secrets
from datetime import datetime

import initiallights_pb2
import initiallights_pb2_grpc

class LoginToken:
    def __init__(self):
        self.token = secrets.token_urlsafe()
        self.date = datetime.now()

    def __repr__(self):
        return '{}: {}'.format(self.date, self.token)

class User:
    def __init__(self, email, password, fullName):
        self.email = email
        self.password = password
        self.fullName = fullName
        self.tokens = {}

    def login(self, password):
        if password == self.password:
            token = LoginToken()
            self.tokens[token.token] = token
            print('{}: login session {}'.format(self.email, token.token))
            return token.token
        else:
            return ''

    def logout(self, token):
        if token == '':
            print('{}: logout from all sessions'.format(self.email))
            self.tokens.clear()
        else:
            print('{}: logout session {}'.format(self.email, token))
            self.tokens.pop(token, None)

class Authorization(initiallights_pb2_grpc.AuthorizationServicer):
    def __init__(self):
        self.users = {}
        self.users['xxx'] = User(email='xxx', password='xxx', fullName='Xxx Yyy')

    def Login(self, request, context):
        success = False
        user = None
        token = None
        if request.email in self.users:
            user = self.users[request.email]
            token = user.login(request.password)
            if token is not None:
                success = True
        message = '' if success else 'email/password combination unknown'
        if success:
            print('login {}'.format(user.email))
            for t in user.tokens.values():
                print('  token: {}'.format(t))
        else:
            print('login failed by {}: {}'.format(request.email, message))
        return initiallights_pb2.LoginResponse(success = success, message = message, email = request.email, token = token)

    def ResetPassword(self, request, context):
        if request.email in self.users:
            print('password reset requested by {}'.format(request.email))
        else:
            print('password reset requested by {0}, but {0} is not registered'.format(request.email))

        return initiallights_pb2.ResetPasswordResponse()

    def RegisterNewUser(self, request, context):
        success = (request.email not in self.users)
        message = '' if success else 'that email is already registered'
        if success:
            print('registered {} (full name: {})'.format(request.email, request.fullName))
        else:
            print('failed to register {}: {}'.format(request.email, message))
        return initiallights_pb2.RegisterNewUserResponse(success = success, message = message)

    def Logout(self, request, context):
        if request.email in self.users:
            user = self.users[request.email]
            user.logout(request.token)
            print('logout {}'.format(user.email))
            for t in user.tokens.values():
                print('  token: {}'.format(t))
        else:
            print('logout requested by {0}, but {0} is not registered'.format(request.email))
        return initiallights_pb2.LogoutResponse()

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    initiallights_pb2_grpc.add_AuthorizationServicer_to_server(Authorization(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()
