#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;


int buffer[15];
int count = 0;
bool bufferedModified = false;
int r1;


// class MyClass {       // The class
//   public:             // Access specifier
//     int myNum;        // Attribute (int variable)
//     string myString;  // Attribute (string variable)
// };




// the produce method
void* producer(void* arg)
{
    // checks if the buffer is being modified
    if (bufferedModified == false)
    {
        bufferedModified = true;
        int i;
        while (true)
        {
		// generates a random number from 0-15
            int N = 15;
            i = rand() % N;

            if (count <= 14)
            {
		    // adds a new item to the buffer
                buffer[count] = i;
                count++;
                cout << "added at " << count << " " << buffer[count] << endl;
            }
            else
            {
		    // sleeps and then rechecks
                cout << "slept " << count << endl;
                bufferedModified = false;
                sleep(0.10);
            }
        }
        bufferedModified = false;
    }

}

// the consume method
void* consumer(void* arg)
{
    // checks if the buffer is being modified
    if (bufferedModified == false)
    {
        bufferedModified = true;
        int i;
        while (true)
        {
            if (count >= 0)
            {
		    // displays a value from the buffer
                i = buffer[count];
                cout << "removed at " << count << " " << buffer[count] << endl;
                count--;
                cout << i << endl;
            }
            else
            {
		    //sleeps for 0.10 of a second and then rechecks
                cout << "slept " << count << endl;
                bufferedModified = false;
                sleep(0.10);
            }

        }
        bufferedModified = false;
    }

}

int main(int argv, char* argc[])
{
    pthread_t producerThread, consumerThread;


    // pthread_attr_t initialization
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //creates the producer and cosnumer threads
    r1 = pthread_create(&producerThread, &attr,
        producer, NULL);
    if (r1) {
        cout <<
            "Error in creating thread" << endl;
        exit(-1);
    }

    r1 = pthread_create(&consumerThread, &attr,
        consumer, NULL);
    if (r1) {
        cout <<
            "Error in creating thread" << endl;
        exit(-1);
    }

    // destroying the pthread_attr
    pthread_attr_destroy(&attr);

    // Joining the thread
    r1 = pthread_join(producerThread, NULL);
    if (r1) {
        cout << "Error in joining thread" << endl;
        exit(-1);
    }

    r1 = pthread_join(consumerThread, NULL);
    if (r1) {
        cout << "Error in joining thread" << endl;
        exit(-1);
    }

    // Exiting thread
    pthread_exit(NULL);

    return 0;
}
