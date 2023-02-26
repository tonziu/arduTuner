# Guitar Tuner using an Arduino board

This project is a simple realization of a basic guitar tuner using an Arduino board. This project was realized in 2017 as a fun project to learn about arduino programming.

## Inspiration 

Tuned guitar strings emitted signals, in the frequency domain, are characterized by specific frequencies:

$$
\begin{aligned}
 f(E_{low}) &= 82.41\ Hz\\
 f(A) &= 110\ Hz \\
 f(D) &= 146.83\ Hz \\
 f(G) &= 196\ Hz \\
 f(B) &= 246.94\ Hz \\
 f(E_{high}) &= 329.63\ Hz
\end{aligned}
$$

<p align='justify'>
This simple consideration can be used to design a simple guitar tuner. The spectrum of a tuned string should have its peak in a restricted interval of the fundamental frequency of the corresponding string. The basic idea for this project is then to acquire the sound emitted by a single guitar string picked by the user and calculate its Fourier transform to analyze its spectrum. Each string can be associated with two frequency intervals: $\Delta f_{ext}$ and $\Delta f_{int}$. Let $f_{fund}$ be the fundamental frequency of the considered string, we can define
</p>

$$
\begin{aligned}
  \Delta f_{ext} &= f_{fund} \pm \delta_{ext} \\
  \Delta f_{int} &= f_{fund} \pm \delta_{int}
\end{aligned}
$$

<p align='justify'>
where $\delta_{ext} > \delta_{int}$ define the width of both intervals. Given the string spectrum, its peak can be localized and compared to all possible frequencies intervals defined as stated below. The external interval can be used to understand which string is being picked, the internal one can be used to notify the user about the state of the current string tuning. The user is notified about the tuning state of a string using three leds. A green one indicates that the string is tuned, a blue one indicates that the pitch is too low and a red led indicates that the pitch is too high. 
</p>

## Experimental Setup

Let's take a look at the experimental setup:

<p align="center">
<img src="https://user-images.githubusercontent.com/62934042/221425749-fffaae9e-3795-43b6-a170-007ce1abf8ac.png" alt="Setup" width="600" height="400" title="Setup">
</p>

<p align='justify'>
In the visual representation, a STM32 board from ST-Microelectronics is shown but the considerations are valid for an Arduino board too. A sound sensor which integrates a microphone and a conditioning system is connected to the board via its analogic output. A button is used to enable the acquisition of the strings signal. A white led is used to notify the user that the system is ready to acquire the signal.
</p>

:warning: **This repository is a work in progress.**
