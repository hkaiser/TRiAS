

/*
 *
 *          Copyright (C) 1996, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1996. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */


#if defined(__GNUC__)
#pragma implementation
#endif


#include "base/segseq.h"

// ------------- Implementation of the CL_SegmentedSequence class ---------




static CL_SegDesc _NullSegDesc = { 0, 0 };

// Addressing scheme: low 13 bits are offset; next higher 13 bits are
// segment number. We maintain this invariant: there are _numSegs segments,
// among which the first _numSegs-1 are "full", i.e., have 0x1fff+1 == 8192
// cells. The remaining (last) segment will have the following size: if the
// capacity needed is c, then the first _numSegs-1 segments contribute
// (_numSegs-1)*8192 bytes (as above), so the last segment will have the
// nearest higher power of 2 above c - (_numSegs-1)*8192 cells.




static short NearestHigher2Power (short l)
{
    // This function only works for l <= 16383
    if (l == 0)
        return 0;
    short mask = 0x4000;
    short old_mask;
    do {
        old_mask = mask;
        mask >>= 1;
    } while (!(mask & l));
    return (mask == l) ? l : old_mask;
}

CL_SegmentedSequence::CL_SegmentedSequence (long initial_cap)
{
    _totalCap = maxl (initial_cap, 8);
    _numSegs   = (short) ((_totalCap >> 13) + 1);
    _segs = new CL_SegDesc [_numSegs];
    if (!_segs) {
        // No memory
        _totalCap = _numSegs = 0;
        return;
    }
    short i = 0;
    for (; i < _numSegs-1; i++) {
        _segs[i]._data = new long[0x1fff + 1];
        if (!_segs[i]._data) break;
        _segs[i]._cap = 0x1fff + 1;
    }
    _numSegs = i;
    short needed = (short) (_totalCap & 0x1fff); // Size of last segment
    if (needed) {
        needed = NearestHigher2Power (needed);

        // Allocate segment
        _segs[i]._data = new long[needed];
        if (!_segs[i]._data)
            return;
        _numSegs++;
        _segs[i]._cap = needed;
        _totalCap = ((_numSegs-1) << 13) | needed;
    }
}

CL_SegmentedSequence::~CL_SegmentedSequence ()
{
    for (short i = 0; i < _numSegs; i++)
        if (_segs[i]._data)
            delete [] _segs[i]._data;
    delete [] _segs;
}





bool CL_SegmentedSequence::ResizeTo    (long new_cap)
{
    if (_totalCap >= new_cap && _totalCap < new_cap + 0x1fff + 1)
        return TRUE;

    // First let's reallocate the "segments" array
    short segs_needed = (short) (new_cap >> 13);  // Total # segments needed
    if (new_cap & 0x1fff)
        segs_needed++;
    short seg_diff = segs_needed - _numSegs; // Number of new segments
                                             // (may be positive or negative)
    if (segs_needed != _numSegs) { // We need a different number of segments
        CL_SegDesc* dsc = new CL_SegDesc[segs_needed];
        if (!dsc)
            return FALSE;
        short n = (short) minl (_numSegs, segs_needed);
        short i = 0;
        for (; i < n; i++)
            dsc[i] = _segs[i];
        if (n < _numSegs) {
            // If the number of segments is less than before, get rid of
            // excess segments
            for (i = n; i < _numSegs; i++)
                delete [] _segs[i]._data;
            _numSegs = n;
        }
        if (_segs)
            delete [] _segs;
        _segs = dsc;
    }    
    if (new_cap > _totalCap) { // Need to grow
        CL_SegDesc lastSeg = _NullSegDesc;
        if ((_totalCap & 0x1fff) == 0) {
            // Our capacity is currently an exact multiple of 8192, so
            // retain the current last segment in the new data structure
            for (short i = _numSegs; i <= segs_needed-2; i++) {
                _segs[i]._data = new long [0x1fff + 1];
                if (!_segs[i]._data)
                    return FALSE;
                _segs[i]._cap = 0x1fff + 1;
            }
        }
        else {
            // Our current capacity is  not an exact multiple of 8192, so
            // we'll grow the last segment
            lastSeg = _segs[_numSegs-1];
            if (seg_diff >= 1) {
                // Allocate the all but the last segment
                for (short i = _numSegs-1; i <= segs_needed-2; i++) {
                    _segs[i]._data = new long [0x1fff + 1];
                    if (!_segs[i]._data)
                        return FALSE;
                    _segs[i]._cap = 0x1fff + 1;
                }
            }
        }
        // Allocate the new last segment
        short last_seg_size = NearestHigher2Power ((short) (new_cap & 0x1fff)); 
        if (last_seg_size == 0)
            last_seg_size = 0x1fff + 1;
        else
            last_seg_size = (short) maxl (8, last_seg_size);
        long* p = new long [last_seg_size];
        if (!p)
            return FALSE;
        short last_seg_index = _numSegs + seg_diff - 1;
        _segs[last_seg_index]._data = p;
        _segs[last_seg_index]._cap = last_seg_size;

        if (lastSeg._cap != 0) {
            // The old capacity was not an exact multiple of 8192, so we
            // must have grown the last segment. Therefore,
            // copy back the contents of the old last segment
            for (short i = 0; i < lastSeg._cap; i++)
                _segs[_numSegs-1]._data[i] = lastSeg._data[i];
            delete [] lastSeg._data;
        }
        _numSegs += seg_diff;
        _totalCap = last_seg_size + (_numSegs-1) * (0x1fffL + 1);
    }
    else { // new_cap < totalCap
        // We've already destroyed the excess segments; we just need to
        // shrink the last segment

        short last_seg_size;
        if (new_cap & 0x1fff) {
            // The new capacity is not an exact multiple of 8192, so we
            // have to shrink the last segment. Therefore,
            // copy back the contents of the old last segment
            last_seg_size = NearestHigher2Power ((short) (new_cap & 0x1fff)); 
            if (last_seg_size == 0)
                last_seg_size = 0x1fff + 1;
            else
                last_seg_size = (short) maxl (8, last_seg_size);
            short current_cap = _segs[_numSegs-1]._cap;
            if (last_seg_size*2 >= current_cap &&
                last_seg_size < current_cap) { 
                // We hang on to memory a little longer, if the shrinkage
                // is not too much
                return TRUE;
            }
            long* p = new long [last_seg_size];
            if (!p)
                return FALSE;
            short l = _numSegs-1;
            short m = (short) minl (current_cap, last_seg_size);
            for (short i = 0; i < m; i++)
                p[i] = _segs[l]._data[i];
            delete [] _segs[l]._data;
            _segs[l]._data = p;
            _segs[l]._cap  = last_seg_size;
        }
        else
            last_seg_size = 0x2000;
        _numSegs = segs_needed;
        _totalCap = last_seg_size + (_numSegs-1) * (0x1fffL + 1);
    }
    return TRUE;
}

