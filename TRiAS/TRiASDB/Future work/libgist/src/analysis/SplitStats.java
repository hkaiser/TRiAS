// SplitStats.java
// Copyright (c) 1998, Regents of the University of California
// $Id: SplitStats.java,v 1.1 1999/06/21 00:33:20 marcel Exp $


///////////////////////////////////////////////////////////////////////////////
// SplitStats -
// 	Java-equivalent of amdb_splitstats::FullSplitStats
//
// Description:
///////////////////////////////////////////////////////////////////////////////

public class SplitStats
{

float preIos;
float optIos;
float actualIos;
float preExcCovLoss;
float actualExcCovLoss;

float optClusterDelta;
float actualClusterDelta;
float clusterLoss;
float clusterOh;
float clusterSuccess;
float excCovDelta;
float excCovLoss;
float excCovOh;
float excCovSuccess;

SplitStats()
{
    reset();
}

void
reset()
{
    preIos = 0.0f;
    optIos = 0.0f;
    actualIos = 0.0f;
    preExcCovLoss = 0.0f;
    actualExcCovLoss = 0.0f;

    optClusterDelta = 0.0f;
    actualClusterDelta = 0.0f;
    clusterLoss = 0.0f;
    clusterOh = 0.0f;
    clusterSuccess = 0.0f;
    excCovDelta = 0.0f;
    excCovLoss = 0.0f;
    excCovOh = 0.0f;
    excCovSuccess = 0.0f;
}

}
