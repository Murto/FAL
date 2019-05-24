# FAL

## Overview

FAL (Finite Automaton Language) is a language for specification of finite state automata, and a tool for processing those specifications into formats which allow them to be visualised.

See the FAL language specification (`docs/language.md`) for more details.


## Dependencies

FAL depends on the Boost program\_options and Graphviz libraries. Ensure that these are installed prior to attempting to build FAL.


## Building

Building FAL will result in an executable tool that will transform a given specification of a finite state machine into a given format.

A build script is supplied in the project's root directory to streamline the process:

```bash
sh build.sh
```

If completed successfully, a `fal` executable will now be available in a new `build` directory.


## Installation

Installing FAL goes a step further than building and places a `fal` executable into a system wide directory so that it can be used anywhere on your system.

An install script is supplied in the project's root directory to streamline the process:

```bash
sh install.sh
```

If completed successfully, a `fal` executable will now be available for the system.

You may need to use `sudo` for this part.


## Use

The `fal` executable can be used to transform finite state machine specification written in the FAL language (see `docs/language.md`) into several different formats.

Usage:

```bash
fal file format
```

The following formats are available:

| Format | Output |
| --- | --- |
| dot | A .dot file that can be used with graphviz tools |
| gif | A .gif image |
| png | A .png image |
| ps | A .ps (PostScript) file |
| svg | A .svg image |
