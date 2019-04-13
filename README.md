Yamaha VST3 Plugin for Ableton
==============================

Introduction
------------

Ableton 10.1 beta promises VST3 support.

I thought this would be an ideal opportunity to try the VST3 instrument provided by YAMAHA. I couldn't get it to work in any sensible way.
It seems to use propriertary communication, which prevented it from syncing settings when launched from within Ableton. 

Even when launched from outside Ableton, it takes a lifetime to sync.

I know I should be creating music, rather than creating plugins - but I thought I'd give this one a go. This project is written using C++
with Juce framework - which is free for hobbyist/non-commercial use. Juce provides a framework for creating VST3 plugins.

How it works?
-------------

This plugin is very simple.

The MOXF has two ports:
- the normal data port, Port 1
- the editor port, Port 4

The following interaction diagram shows a lifecycle for this plugin

```
    Ableton                   Plugin            MOXF
        |                         |               |
        |_                        |               |
        | | create new set        |               |
        |</                       |               |
        |                         |               |
        |  add plugin to track    |               |
        |------------------------>|               |
        |                         | Send bulk dump|
        |                         |    of mixer   |
        |                         |<--------------|
        |                         |               |
        |                         |               |
        |                         |  Parameter    |
        |                         |    change(s)  |
        |                         |<--------------|
        |                         |               |
        |                         |               |
        |_                        |               |
        | | save set              |               |
        |</                       |               |     
        |    Persist MOXF State   |               |
        |<------------------------|               |
        |                         |               |
```
When the set is reloaded...
```
    Ableton                   Plugin            MOXF
        |                         |               |
        |_                        |               |
        | | load set              |               |
        |</                       |               |
        |                         |               |
        |  reinstate MOXF state   |               |
        |------------------------>|               |
        |                         | Send bulk dump|
        |                         |    to mixer   |
        |                         |-------------->|
```

Pre-requisites
--------------

You'll need:
- the VST3 SDK available from [Steinberg](https://www.steinberg.net/en/company/developers.html)
- Juce SDK available from [Juce](https://shop.juce.com/get-juce)
- XCODE (haven't tested it on Windows)



