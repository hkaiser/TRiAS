//////////////////////////////////////////////////////////////////////////////
// Return values for TestDroppablePoint 
#define UDROP_NONE              0x0000      // Exclusive
#define UDROP_CLIENT            0x0001      // Inclusive
#define UDROP_INSETLEFT         0x0002      // L/R are exclusive
#define UDROP_INSETRIGHT        0x0004
#define UDROP_INSETHORZ         (UDROP_INSETLEFT|UDROP_INSETRIGHT)

#define UDROP_INSETTOP          0x0008      // T/B are exclusive
#define UDROP_INSETBOTTOM       0x0010
#define UDROP_INSETVERT         (UDROP_INSETTOP|UDROP_INSETBOTTOM)

#define UDROP_INSET				(UDROP_INSETHORZ|UDROP_INSETVERT)

