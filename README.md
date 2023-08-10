# Mercury v0.1.0

## What is Mercury?

Mercury is a **lightweight C++ publisher-subscriber library** developed for use in the VEX Robotics Competition. The library is a **PROS template** that follows in the footsteps of frameworks like ROS by enabling students to **write simple messaging code** that lets the different subsystems of a robot communicate with each other in a **thread-safe, asynchronous** manner.

## What is pub-sub?
**Publisher-subscriber**, or **pub-sub**, systems are a way to allow communication between the various parts of a system. 

Let's say you had a robot with a button sensor mounted to the front of its chassis, and you wanted to stop the robot from driving forward when the button was pressed. Using pub-sub messaging, you would create a publisher for the button sensor and a subscriber for the chassis motors. The publisher would be set up to publish a certain value representing the button's state (pressed or not pressed) to a specific topic. The subscriber would then subscribe to that topic, and any time a value was published to the topic, it would receive that value and perform some operation with it.

This may seem like a lot of work for just one button, but if you wanted to add another subsystem that checked for that same button press, all you would need to do was add another subscriber. Mercury simplifies this even further by **taking care of the messaging for you.** All you do is specify your publishers and subscribers.

## Installation

To use Mercury, all you need to do is download the latest ZIP file from the Releases page. Then, using the PROS integrated terminal, run
```bash
pros c fetch mercury@x.x.x.zip
```
replacing 'x.x.x' with the required version number.

Finally, navigate to your PROS project and run
```bash
pros c apply mercury
```

## Usage

Creating a `Publisher` is as simple as a single line of code:
```cpp
mercury::Publisher<int> publisher("topic_name");
```

This line creates a `Publisher` with integer message type and topic name `"topic_name"`. If you want a different message type, just swap out the `int` for any other type.

Creating a `Subscriber` is a bit more involved. First, you need a function that takes in a single parameter, like this:
```cpp
void subscriber_callback(int data) {
    printf("%d\n", data);
}
```

This function will be called on the messages that the subscriber will be receiving, so make sure the type of the parameter matches the type of the topic being subscribed to. Then, make a `Subscriber` with this line:
```cpp
mercury::Subscriber<int> subscriber("topic_name", subscriber_callback);
```
This `Subscriber` is subscribed to the `"topic_name"` topic we made with that previous `Publisher`, and it is set up with the `subscriber_callback` function.

Now, whenever you want to communicate between the `Publisher` and the `Subscriber`, just write:
```cpp
publisher.publish(data)
```

and the `Subscriber` will receive the `data` integer.