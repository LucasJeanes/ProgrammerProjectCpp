# 🌧️ Digital Rain — Matrix Effect in C++

Inspired by the iconic Matrix digital rain, this project simulates cascading streams of characters across the console window using C++. The animation is multithreaded, customizable, and fully terminal-based.

---

## 📌 Overview

This project prints falling streams of random ASCII characters that mimic the Matrix digital rain. It uses Windows-specific console functions to move the cursor and apply colours, along with modern C++ features such as:

- `std::thread` for concurrent raindrops
- `std::mutex` for thread-safe printing
- `std::random_device` and `std::mt19937` for robust randomness
- A custom console manager for low-level display control

---

## 🛠️ Features

- Dynamic rain column generation using multithreading
- User-configurable:
  - Number of raindrops
  - Trail length
  - Speed & heaviness (density)
  - Console dimensions
  - Colour customization (Matrix green, red chaos, ice blue, etc.)
- Cleaned up display: blinking cursor hidden
- Thread-safe character printing using scoped mutexes

---

## 🎬 How It Started

The first thing I tried to do was using the `GoToXY` function given in the lab to print a column of characters. I wanted the characters to be random so I used a random number generator function to generate integers in the range of 32-126, then converted that into the relevant ascii character to be printed. 0-31 and 127 aren’t printable ascii characters so those values were omitted. 

I used an arbitrary 23 character long column as it natively fit within the created terminal window.
On the random numGenerator, I learned that `rand()` is outdated, so I switched to C++'s `<random>` library to generate better randomness with `std::mt19937`. Some [good insights on this here](https://stackoverflow.com/questions/53040940/why-is-the-new-random-library-better-than-stdrand).
After it prints the full column, it goes back to the top and reprints a whitespace “ “ character to remove the trail.

This was the first iteration of the code for printing the characters using the GoToXY() function!

![image](https://github.com/user-attachments/assets/cac055b7-629e-4331-a2d7-14d3420d5964)

Pretty good output for the first steps!

![image](https://github.com/user-attachments/assets/9a9f7b5a-a39c-4b79-aed2-b0da7dc87836)

---

## 🎨 Adding Colour

Once I had that working, the next step was to add colour. You can’t have matrix/digital rain without the classic green text, and I wanted to make the trail of characters green while keeping the current character white. 

StackOverflow came to the rescue once again with helpfully supplying the function I needed to create my vibrant green text. A slight modification of my printing function to print the (y – 1) character again but in green, and I was already half-way there. I realized at this point that because I was using GotoXY to control where I was printing, I didn’t need the `endl` tag in my prints so I also removed those as they were redundant.

Updated code!

![image](https://github.com/user-attachments/assets/c2787090-a936-4044-ac40-69637b6e51c9)

It's looking much better now!

![image](https://github.com/user-attachments/assets/073ac36b-aeba-4eb9-b285-1f4a9ec973d8)

**Reference:**  
[Colorizing console output in C++ (StackOverflow)](https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c)

---

## 👁️ Blinking cursors are bad! (and distracting)

- **Removed blinking cursor** using `GetConsoleCursorInfo()` and setting `bVisible = FALSE`.
- Used `system("mode x,y")` to resize the console window dynamically to fit the animation.

I wanted to remove the blinking cursor as it was quite distracting, and very quickly I [found this Stack Overflow post](https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt) (this is becoming quite a habit) immediately on my initial internet search. By using the handle key for the StdHandle in the windows library, I was able to retrieve the console cursor information and change the cursor visible flag to FALSE which hides the cursor. Quick and easy, StackOverflow gave me the packaged function so it was easy to implement.

**Reference:**
[Blinking underscore](https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt)

---

## 🧵 Threading the Raindrops

To simulate multiple columns of rain independently, I used `std::thread`—one per raindrop. This avoided complicated multi-row state tracking.

Each thread draws its own falling stream using a shared `printMutex` to avoid console collision.

I thought about it for awhile and figured trying to control rows and columns of different positions (I want the rain-drops to be in different vertical positions and not all falling at the same level) would get incredibly messy and I didn’t want to spend hours working with vectors inside vectors. If I could put each raindrop column in its own thread then I wouldn’t have to worry about managing multiple rows of information, I could theoretically copy-paste my existing raindrop function and utilize the GotoXY function to control where the printing and colour changing was occurring due to the specified coordinates.

Thankfully I already understood how threads work from my experience working in embedded syste,s and my own interest in the field, so it was more understanding the syntax than the concept which made this much easier. However the threading still took some effort to get working as there were quite a few things I needed to learn specifically with how C++ handles them. One of the C++ reference docs had a good example, plus I found a very good simple explanation of how they work in (you guessed it!) StackOverflow. 

I also wanted to have the “user” define how many raindrops to create and because this directly impacted how many threads were made, I needed a way to create and join the threads without explicitly creating each handle manually myself. I decided to try implementing this using a vector, “for each” loops work great in this scenario.
The examples I found used `vector.push_back()` when creating threads within a vector and while looking for supporting documentation about this functionality, I found this [fantastic article](https://www.geeksforgeeks.org/vectoremplace_back-c-stl/) that went into depth on `vector.emplace_back()` which also compared it with the `vector.push_back()` option. 

The article highlighted that `emplace_back()` was more efficient in placing the elements at the back of the vector as it created the element in-place within the vector, while `push_back()` created the object first, then copied it to the function which seemed like unnecessary extra steps (and wasteful computation resources). If I was creating large amounts of raindrop threads, this could be problematic as I didn’t want it doing extra creations + copies for every thread.

Look at it, isn't it beautiful? Notice anything strange about it?

(hint: The current white character isn't at the bottom of the raindrop! Weird gaps in the trail too. Ignore the big gap, I was testing some range values for the `GoToXY` function as well)

![image](https://github.com/user-attachments/assets/49d05f24-bfdd-4ec8-9a4d-c58e35b76755)

**References:**
- [C++ std::thread (cplusplus.com)](https://cplusplus.com/reference/thread/thread/thread/)
- [Simple C++ threading example (StackOverflow)](https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c)
- [efficiency article on vector.push_back() vs. vector.emplace_back()](https://www.geeksforgeeks.org/vectoremplace_back-c-stl/)

---

## 🔒 Fixing Thread Collisions

Initially, threads would overwrite each other’s characters causing display glitches. I solved this using `std::mutex` and `std::lock_guard`.

To optimize performance:
- I scoped the mutex locks only around each individual print
- I added `std::this_thread::yield()` to prevent greedy thread hogging

I noticed a printing bug when I created multiple threads of `RainEffect`, very noticeable especially with the colour option for previous characters. The currently printing character is white, and it sets the previous character (using GoToXY function for y – 1 and re-printing the previous white character as green) before continuing on. The console can only print one character at a time despite multiple threads so each thread was attempting to print and making it very messy. It broke the logical flow of the program to generate the column of characters as we saw in the previous screenshot.
I've touched on mutexes and thread-safe operations with my time in embedded systems and remembering how the printing function can be interrupted, I looked for mutex functionality in C++ so see if I could make the printing thread-safe between the multiple threads.

One more look because we can.

![image](https://github.com/user-attachments/assets/9f606aea-e8a7-46eb-a716-8f42eed5448e)

I was surprised at how "easy" it was to implement, I found the mutex page in the [Cpp reference docs](https://en.cppreference.com/w/cpp/thread/mutex) and just by using the included example I was able to implement it. It did take some playing around with restricting where the mutex was applied as it was crashing the program + making it very slow. 

Solution: Limiting the scope of where the mutex is enabled helped to reduce the wait time, and it removed the `Abort()` termination errors I was getting. I learned that the mutex `lock_guard` only gives back the mutex when it leaves the scope of where it was called, so I had to wrap each mutex within its own parenthesis for each print function to help control the scope better.
To be extra “thread” safe I included a `std::this_thread::yield()` at the end of the `RainEffect` class to yield the thread so other threads can take over, as there was a small bug where the first thread was taking priority and stopping the other threads from fully completing their code block. How greedy!

Hey, this is looking a lot better now!
![image](https://github.com/user-attachments/assets/bfc31cb0-57c3-46d7-b77c-03690ce797f9)

**Reference:**  
[std::mutex and lock_guard (cppreference)](https://en.cppreference.com/w/cpp/thread/mutex)

---

## 🖥️ How to Use

1. Compile the project using any C++17+ compatible compiler (Windows only).
2. Run the executable. You'll be prompted for:
   - Raindrop count
   - Trail length
   - Console dimensions
   - Drop speed and spacing (heaviness)
   - Colour customization

---

## 📸 Demo of final version!
(It runs smoothly in the terminal, included GIFs here seem to stutter)

![Digital Rain Demo](digital_rain_loop.gif)

---

## 📚 References

See above inline links or:
- [Colorizing console output in C++ (StackOverflow)](https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c)
- [Blinking underscore](https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt)
- [C++ std::thread (cplusplus.com)](https://cplusplus.com/reference/thread/thread/thread/)
- [Simple C++ threading example (StackOverflow)](https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c)
- [efficiency article on vector.push_back() vs. vector.emplace_back()](https://www.geeksforgeeks.org/vectoremplace_back-c-stl/)
- [std::mutex and lock_guard (cppreference)](https://en.cppreference.com/w/cpp/thread/mutex)

---

## 🧠 Lessons Learned

- Threading is powerful but requires careful management (mutexes, scope).
- `GotoXY` and colour codes give low-level control over the console—great for CLI graphics.
- Console IO + threads = race conditions unless protected.
- It's fun recreating iconic visual effects with basic terminal tools!

---

## 🔗 Future Improvements (If Time Allowed)

- Add animation modes or presets (e.g. Pulse effect, consolidating random characters to "reveal" a hidden message in the center)
- Cycle colours or trigger theme changes over time
- Export user config profiles
- Render as a full screen saver

---

Made with ☕, `std::thread`, and a lot of stack overflow!
