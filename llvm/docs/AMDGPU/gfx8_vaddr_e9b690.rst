..
    **************************************************
    *                                                *
    *   Automatically generated file, do not edit!   *
    *                                                *
    **************************************************

.. _amdgpu_synid_gfx8_vaddr_e9b690:

vaddr
=====

Image address which includes from one to four dimensional coordinates and other data used to locate a position in the image.

*Size:* 1, 2, 3, 4, 8 or 16 dwords. Actual size depends on opcode and specific image being handled.

    Note 1. Image format and dimensions are encoded in the image resource constant but not in the instruction.

    Note 2. Actually image address size may vary from 1 to 13 dwords, but assembler currently supports a limited range of register sequences.

*Operands:* :ref:`v<amdgpu_synid_v>`
