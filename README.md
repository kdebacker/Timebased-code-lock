# Timebased-code-lock

A proof of concept for a safe with a timebased code lock, the code for this lock will be available on the smartphone.
The calculation of the code is based on the same principle as existing authenticators like the ones used for 2-factor authentication.

This has been implemented on a PIC 16F887 with a 20MHz crystal which was used to run this code, and a DS1307 with a 32.768kHz crystal which was used to keep the time.

Disclaimer: This was made for a high school project back in 2014.
