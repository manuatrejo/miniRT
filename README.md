_This project has been made as part of the 42 curriculum by Maanguit, Amonteag

# **miniRT**

# **Description**

**miniRT** is a small ray tracing program developed in **C** as part of the **42 Common Core**.
The goal of the project is to understand the foundations of ray tracing: generating rays from a camera, intersecting those rays with geometric objects, computing surface normals, and shading pixels to produce an image.

In this implementation, the program reads a scene description from a **`.rt`** file, parses it strictly following the project format, builds an internal scene representation, and renders the result using **MiniLibX**.

This project includes (depending on the scene used):

- A strict **`.rt` parser** (format validation + error handling)
- A **camera** with configurable FOV
- Basic objects and intersections:
- **Sphere** (`sp`)
- **Plane** (`pl`)
- **Cylinder** (`cy`)
- **Cone / double-cone (bicone)** (`cn`) *(bonus / custom extension in this repo)*
- **Materials** (albedo / metallic / roughness) and a **path tracing** style shading pipeline
- Support for **MiniLibX** window creation and image display

# **Instructions**

## **Requirements**

To compile this project you need:

- A C compiler (`cc` / `gcc` / `clang`)
- `make`
- X11 development libraries (for MiniLibX on Linux)

On Debian/Ubuntu you can install the usual dependencies with:

```bash
sudo apt update
sudo apt install build-essential xorg libxext-dev libx11-dev zlib1g-dev
```

> Note: This repository uses **MiniLibX for Linux** under `minilibx-linux/`.

## **Installation**

Clone the repository (SSH):

```bash
git clone git@github.com:manuatrejo/miniRT.git
```

Enter the project folder:

```bash
cd miniRT
```

## **Compilation**

Compile the project with:

```bash
make
```

Optional build parameters available in the `Makefile`:

- `SAMPLES` – path tracing samples per pixel
- `CHECK` – enable/disable checkerboard shading

Example:

```bash
make re SAMPLES=8 CHECK=1
```

## **Usage**

Run the program with a scene file:

```bash
./miniRT scenes/mandatory/00_pl_sp_cy_basic.rt
```

Bonus scenes are available here:

```text
scenes/bonus/
```

Example:

```bash
./miniRT scenes/bonus/03_cn_apex_closeup.rt
```

### **Scene format notes**

- The parser is strict: **unknown identifiers** or malformed tokens will fail.
- Camera direction vectors must be **normalized**.
- This project’s parser does **not** treat `#` as comments (avoid inline comments in `.rt`).

# **Resources**

To make the development of this project possible, the following resources were helpful:

- Ray Tracing Fundamentals, Ray Tracing in one weekend, Ray Tracing in one week
- PBRT (Physically Based Rendering) concepts (BRDF / sampling)
- MiniLibX (Linux) documentation and examples
- The 42 **miniRT** subject PDF

Additionally, AI tools such as GitHub Copilot and ChatGPT were used **strictly as learning and research aids**.

They were mainly consulted to better understand:

- Ray/object intersection math
- Computing normals and handling edge cases
- BRDF intuition (diffuse vs specular) and sampling ideas
- Debugging strategies (Valgrind, invariants, numeric EPS issues)

All architectural decisions, logic design, and code implementation were done manually.
