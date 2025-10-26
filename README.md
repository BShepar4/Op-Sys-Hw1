Homework assignment for Operating Systems
10/22/2025


HOW TO USE
Open VS Code
Connect To WSL 
Clone Git Repository with link: https://github.com/BShepar4/Op-Sys-Hw1.git

Open a terminal and run three commands
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer &

The code has no defined endpoint. To cancel it, open a second terminal 
Run pkill producer and pkill consumer to stop the code from running

producer.cpp 
Creates the producer, which creates 2 integers and then adds them into shared memory

consumer.cpp 
Creates the consumer, which prints off integers from the shared memory and then sets their value to zero
