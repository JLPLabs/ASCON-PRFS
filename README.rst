ASCON-PRFS
==========

Demonstration of creating 8 byte tags using ASCON Psuedo-Random Function Short

Note that the ASCON PRF "short" form means the input message to tag is <= 16 bytes and the tag is also <= 16 bytes.


::

  Demonstration of ASCON-PRFS

  key        (hex) : 000102030405060708090a0b0c0d0e0f
  base msg   (hex) : 4379636c6f6e65733230323421000000
  ...........................................................
  base msg (ascii) : [Cyclones2024!]

  note: the last three bytes of the base message are updated with a nonce value
  and then a tag generated.


  nonce               msg (w/nonce)                     tag
  ------------------  --------------------------------  -----------------
    1000 (0x0003e8)  4379636c6f6e657332303234210003e8  51eef9b8733a73fb
    20000 (0x004e20)  4379636c6f6e65733230323421004e20  ab4ad516d465047e
  100000 (0x0186a0)  4379636c6f6e657332303234210186a0  6b96250a86382ac7
  1000000 (0x0f4240)  4379636c6f6e657332303234210f4240  c11cdd72b7deead1
