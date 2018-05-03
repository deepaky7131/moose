# Critical Stretch UserObject

## Description

UserObject `CriticalStretchUserObject` is used to assign values for the `critical_stretch` auxiliary variable. The values can be uniform for all bond or follow normal distribution.

The same sampling should be applied to all the bonds, and usage of GeneralUserObject rather than AuxKernel can achieve this purpose by avoiding repetition of the same sampling procedure to partial bonds on each processor.

!syntax parameters /UserObjects/CriticalStretchUserObject

!syntax inputs /UserObjects/CriticalStretchUserObject

!syntax children /UserObjects/CriticalStretchUserObject
