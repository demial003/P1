For our test plan we wrote 7 tests, three of which just test the errors we need to send.

1. testThings - a general test that makes sure our malloc and free preserve old chunks. We create three chunks and free the second one 
leaving a gap in betwee the first and third. We then ask for a new chunk of the same size of the second and compare the addresses of the
second and fourth chunks. If they are the same then we know we reused the chunk from the second call that we freed earlier.

2. testCoalesce - a test to make sure our free function coalesces adjacent empty chunks appropriately. We create two 2040 byte chunks and then free them.
We then make a chunk double the size of those two and compare the address of the start of this chunk to the start of the first chunk we made. If they are
the same then we know our free combined the two previous chunks into one larger shunk

3. testDeallocation - a test to make sure free deallocates memory. We request a chunk and then free it. We then look into that chunks header to make sure
the chunk is marked as free(status 0). If it is we know the chunk was properly deallocated.

4. testLeak - we basically just call malloc without free and make sure we correctly identify leaked objects.