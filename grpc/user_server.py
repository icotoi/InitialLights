from concurrent import futures
import logging

import grpc

import initiallights_pb2
import initiallights_pb2_grpc


class User(initiallights_pb2_grpc.UserServicer):

    def Login(self, request, context):
        success = (request.email == 'xxx' and request.password == 'xxx')
        message = '' if success else 'email/password combination unknown'
        if success:
            print('login ok (email:' + request.email + ')')
        else:
            print('login failed: ' + message + ' (email: ' + request.email + ')')
        return initiallights_pb2.LoginResponse(success = success, message = message, email = request.email)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    initiallights_pb2_grpc.add_UserServicer_to_server(User(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()
