Notable things:
Both FSA and the Heap Allocator put in fill values as well as guard bands.
Heap Allocator's implementation of fill values and guard bands can be found in ./Mallocate/HeapManager.cpp
Initial setup fills the entire allocated heap with guard bands (lines 21-24) and fill values (lines 28-33), and while allocating new memory and making a new block, also performs it on the leftover blocks (line 87 and 106)

FixedSizeAllocator performs a cleaner version of this setup, using memsetPattern in order to fill in given areas of code with the same values.
This can be found on creation (./Mallocate/FixedSizeAllocator.cpp, lines 25-28) and whenever blocks are freed (line 67)

All of the various Controllers for Monster Chase have move constructors set up, which can be found in their respective files, in ./MonsterChase/XXXController.cpp

The Final Exam's sample unit test is found in ./Final/main.cpp.

There's a unit test for the Bit Array class, found in ./Mallocate/Mallocate.cpp, lines 314-360.

By default, all of Mallocate, FinalExamSampleProject, and MonsterChase have been set as startup projects.