Trade program
Minhyung Joo 20173164
-------------
class Server
*Constructor sets up the socket and binds it to an address and port number 5001.
*Every 10th second, the price is updated with a random value.
*Keeps own double price variable which is pulled from the shared memory map initialized in the constructor.
*Sleep is called twice in process_buy_request(). Once after it reads message from client, and another one before it sends the result message.

class Client
*Constructor receives the name and port number of the server, and connects the socket.
*Keeps own double price variable that is updated whenever it receives price information from the server. This price variable is used to form the client buy request message.
*Due to a strange bug that resets memory map value to 0, some enter-keys are ignored to prevent wrong price being sent to the server.
*Sleep is not used in gen_buy_request(). I thought all delays should be simulated in the server side to make the process more realistic(?)

-------------
No external libraries were used.
