# Signaling
Small C++11 library to handle signals between object in an asynchronous and portable way.

It executes some code asynchronously every time a signal is received. The utility here is communicate objects in a simple way, only having to run a method of the Signal object.

## How to use it
Create a Signal object for every signal you want to handle.
For example: `Signal sigStart, sigStep, sigStop;`

Then, assign them code using the `ConfigSignal` macro:
```c++
ConfigSignal(start, {
	state = on;
	speed = defaultSpeed;
});
```
`ConfigSignal` is simply a wrapper that create a new thread, add the functions necessary to wait between executions, and move it in the `Signal` object.

The thread is automatically joined when the `Signal` object is deleted.

To trigger the signal, there is only needed to run the `trigger()` function from anywhere available.

## License

MIT License

Copyright (c) 2021 José Miguel (josemi) Rodríguez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
