// QueryStats.java
// Copyright (c) 1998, Regents of the University of California
// $Id: QueryStats.java,v 1.1 1999/06/21 00:33:20 marcel Exp $


///////////////////////////////////////////////////////////////////////////////
// QueryStats -
// 	combines amdb_wkldprofile::QueryStats and amdb_wkldstats::QueryStats
//
// Description:
///////////////////////////////////////////////////////////////////////////////

public class QueryStats
{

int resultSetLimit; // amdb_wkldprofile::Query.retrLimit
StringBuffer qual; // amdb_wkldprofile::Query.resultSetSize
int resultSetSize; // amdb_wkldprofile::Query.resultSetSize

// amdb_wkldprofile::QueryStats::LeafStats
float avgUtil; // avg. util
int retrievalVol; // size (in bytes) of all retrieved items
int totalLeafIos; // total # of leaves accessed

// amdb_wkldprofile::QueryStats::LeafStats
int totalInternalIos; // total # of internal nodes accessed

// amdb_wkldstats::QueryStats::LeafStats
int minIos; // ceil(total volume retrieved / target page capacity)
int optimalIos; // # of leaf accesses for optimal clustering
float optimalOh; // overhead of optimal clustering w.r.t. theoretical minimum
float optLeafOh; // overhead of leafIos
float minLeafOh;
float randomIos; // avg. # of leaf accesses for random clustering
float randomStdDev; // std. dev. of randomIos
float optRandomOh; // overhead of randomIos
float minRandomOh;
float optClusterLoss; // loss due to clustering
float optClusterOh; // overhead introduced by clustering
float minClusterLoss;
float minClusterOh;
float leafUtilLoss; // loss due to utilization
float utilOh; // overhead introduced by utilization
float leafExcCovLoss;
float excCovOh;

// amdb_wkldstats::QueryStats::InternalStats
float internalUtilLoss; // loss due to utilization
float internalExcCovLoss;

QueryStats()
{
    qual = new StringBuffer();
    reset();
}

void
reset()
{

    resultSetLimit = 0;
    qual.setLength(0);
    resultSetSize = 0;

    avgUtil = 0.0f;
    retrievalVol = 0;
    totalLeafIos = 0;

    totalInternalIos = 0;

    minIos = 0;
    optimalIos = 0;
    optimalOh = 0.0f;
    optLeafOh = 0.0f;
    minLeafOh = 0.0f;
    randomIos = 0.0f;
    randomStdDev = 0.0f;
    optRandomOh = 0.0f;
    minRandomOh = 0.0f;
    optClusterLoss = 0.0f;
    optClusterOh = 0.0f;
    minClusterLoss = 0.0f;
    minClusterOh = 0.0f;
    leafUtilLoss = 0.0f;
    utilOh = 0.0f;
    leafExcCovLoss = 0.0f;
    excCovOh = 0.0f;

    internalUtilLoss = 0.0f;
    internalExcCovLoss = 0.0f;

}

}
