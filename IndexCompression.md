In the [SIGGRAPH talk](https://docs.google.com/present/view?id=d4wf4t2_251g4kjtwgs), I describe how [Google Body](http://bodybrowser.googlelabs.com) performs index compression. It is a basic application of delta-compression. That is, each subsequent index is encoded as the difference from the last. This was a straightforward way to exploit the coherence of optimized triangle indices, and worked very well.

This library uses a slightly different method that exploits coherence even better. For review: by performing ZigZag delta coding from the previous index, the original method implicitly  presumes that the next index is just as likely to be larger than the previous index. However, indices aren't really biased that way.

As you scan the stream of indices, each index is either old or new. The interesting thing that happens after vertex optimization is that new indices are always one larger than the previous largest seen; they'll never jump ahead to some random new index. Therefore, there is a bias for positive deltas to be smaller valued than than negative deltas.

The revised method doesn't use deltas from the previous index. Instead, it keeps track of a _high water mark_ value, which is one more than the largest index yet seen. Old index values are always less than the high water mark, and new index value are always equal to the high water mark. To encode an index, we simply encode the difference between the high water mark and the index. Since this difference is always non-negative, ZigZag is unnecessary.

I haven't compared decompression speed, but I can't imagine that it is substantially different from normal delta coding. I should, of course, confirm that soon.