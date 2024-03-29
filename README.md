About this code
---------------

[PyGame Zero](https://pygame-zero.readthedocs.io/en/stable/)
is a widely-used, widely-deployed interactive graphics library.
It supports interactive, animated 2D graphics with minimum 
"boilerplate" (necessary, typically redundant, and sometimes 
voluminous) code,
positioned especially for learning to write games (including
[migration tutorials](https://pygame-zero.readthedocs.io/en/stable/from-scratch.html)
from 
[Scratch](https://scratch.mit.edu/)), but also of more general use.

This code extends PyGame Zero to support 
[multitouch](https://en.wikipedia.org/wiki/Multi-touch) 
and (hopefully) a growing variety of sensors, embedded displays 
(e.g., LEDs and epaper), and 
actuators (e.g., 
[stepper](https://en.wikipedia.org/wiki/Stepper_motor) and 
[servo](https://en.wikipedia.org/wiki/Servomotor) motors)
used in a variety of 
[XR](https://en.wikipedia.org/wiki/Extended_reality) 
("extended reality") -- e.g., VR, AR, and 
[tangible](https://en.wikipedia.org/wiki/Tangible_user_interface), 
embedded, and embodied interaction 
([TEI](https://tei.acm.org/2022/about/about/)) -- interactions.
Because multitouch (probably the support of greatest 
  popular interest) is not typically considered as XR,
  but XR-related interactions are of greatest interest to 
  the developers, we initially select 
  [Xi](https://en.wikipedia.org/wiki/Xi_(letter)) 
  as an appended descriptor, and pgzx as a common prefix.

[PyGame Zero](https://github.com/lordmauve/pgzero)
dates to at least July 2015. It also has been installed 
by default on 
[Raspberry Pi since September 2015](https://pygame-zero.readthedocs.io/en/stable/installation.html).
It is built upon 
[PyGame](https://en.wikipedia.org/wiki/Pygame), among 
other libraries.
In the PyGame 2.0 October 2020 release (and likely beginning in 
1.9.2), when compiled with SDL2,
the 
[`FINGERDOWN`, `FINGERUP`, `FINGERMOTION`, and `MULTIGESTURE`](https://www.pygame.org/docs/ref/event.html) 
events introduced 
[PyGame support for multitouch interaction](https://www.pygame.org/tags/multitouch).
Among other things, this code extends PyGame Zero to integrate 
these events.

PyGame Zero's sister 
[Wasabi 2D](https://github.com/lordmauve/wasabi2d) game engine
also 
[integrates multitouch support](https://github.com/lordmauve/wasabi2d/blob/master/examples/coroutines/touches.py), 
along with 
[coroutines](https://wasabi2d.readthedocs.io/en/latest/coros.html),
[particle](https://wasabi2d.readthedocs.io/en/latest/particles.html) and 
[post-processing](https://wasabi2d.readthedocs.io/en/latest/effects.html), and other features.

Some elements within supported by NSF CNS-MRI 1828611.

