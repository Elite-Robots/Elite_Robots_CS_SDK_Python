import argparse
import sys
import inspect
import socket
import threading
import time
import elite_cs_sdk as cs



class TcpServer:
    def __init__(self, port: int):
        self.client_socket = None
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.port = port
        self.server_thread = threading.Thread(target=self.__start_tcp_server, args=(port,))
        self.server_thread.daemon = True
        self.server_thread.start()
        self.received_data = None
        
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"TCP Server is started on port {port}")

    def __del__(self):
        if self.client_socket:
            self.client_socket.close()
            cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "TCP Server is closed")
        self.server_socket.close()
        
    def get_received_data(self):
        if self.received_data is not None:
            data = self.received_data
            self.received_data = None
            return data
        return None

    def __handle_client(self, client_socket, client_addr):
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Client is connected: {client_addr}")
        with client_socket:
            while True:
                try:
                    data = client_socket.recv(1024)
                    if not data:
                        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Clinet {client_addr} disconnected")
                        break
                    self.received_data = data.decode()
                except ConnectionResetError:
                    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Client {client_addr} disconnected unexpectedly")
                    break

    def __start_tcp_server(self, port: int):
        self.server_socket.bind(('0.0.0.0', port))
        self.server_socket.listen(5)
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"TCP Server is started, listen port:{port}")

        client_socket, client_addr = self.server_socket.accept()
        self.client_socket = client_socket

        client_thread = threading.Thread(target=self.__handle_client, args=(client_socket, client_addr))
        client_thread.daemon = True
        client_thread.start()



if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Connect to a robot's primary server and perform basic operations."
    )
    
    parser.add_argument(
        "--ip",
        required=True,
        help="IP address of the robot"
    )

    parser.add_argument(
        "--local_ip",
        default="",
        help="Local IP address for the robot to connect back"
    )

    parser.add_argument(
        "--server_port",
        type=int,
        default=50002,
        help="Port number of the server (default: 50002)"
    )
    args = parser.parse_args()

    tcp_server = TcpServer(args.server_port)

    primary = cs.PrimaryClientInterface()

    if(primary.connect(args.ip)):
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Connected to primary server at {args.ip}:{30001}")
    else:
        cs.logErrorMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Failed to connect to primary server at {args.ip}:{30001}")
        sys.exit(1)
    
    local_ip = args.local_ip
    if len(local_ip) <= 0:
        local_ip = primary.getLocalIP()
    
    ROBOT_SOCKET_SEND_STRING = "hello"

    robot_script = "def socket_test():\n"
    robot_script += f"\tsocket_open(\"" + local_ip + "\", " + str(args.server_port) + ")\n"
    robot_script += f"\tsocket_send_string(\"{ROBOT_SOCKET_SEND_STRING}\\n\")\n"
    robot_script += "end\n"
    if (primary.sendScript(robot_script)):
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Robot script sent successfully")
    else:
        cs.logErrorMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Failed to send robot script")
        sys.exit(1)

    time.sleep(5)  # Wait for the robot to execute the script
    
    received_data = tcp_server.get_received_data()
    if received_data is not None:
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Received data from robot: {received_data}")
        if received_data.strip() == ROBOT_SOCKET_SEND_STRING:
            cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Success, robot connected to PC")
        else:
            cs.logErrorMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Fail, robot connected to PC but not send right string")
    else:
        cs.logErrorMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "No data received from robot")
        
    primary.disconnect()
    del tcp_server
