library(wavelets)
############################
# Here is the program
# to be coded for the micro.
# Single function call
# for t (time) and m (mic)
############################

###################################
###################################
# rainmic
# pull rainfall data from mic data
# inputs: t = time (seconds)
#         m = microphone data
# output: zrain
# data frame with one line for
# each SECOND, containing:
#        t = time (rough)
#       totV1 = wavelet1 variance
#       totV2 = wavelet2 variance
#       totV3 = wavelet3 variance
#       totV4 = wavelet4 variance
###################################
###################################
rainmic = function(t,m){
    #############################
    # set up counts, sums, maxima
    # for 1-second totals
    #############################
    seccounter = 0    # count of samples for defining 1-second intervals
                      # trigger at 3333 (1 sec.) and 6666 (2 sec.),
                      # trigger and reset at 10000 (3 sec.)
    meantime = 0
    totV1=0; totV2=0; totV3=0; totV4=0; 
    #######################
    # set up counts, sums
    # for average, variance
    #######################
    mnum = 0     # number summed
    tbar = 0     # average time
    zz = NULL   # data frame to hold 1-second data
    #################################
    # process each data point in turn
    #################################
    ntot = length(m)
    mnum = mnum+1                        # count 1 more
    tbar = tbar+(t-tbar)/mnum      # update time average
    wt <- dwt(m, filter="d4", boundary="periodic")
    totV1 <- var(as.numeric(wt@W$W1))
    totV2 <- var(as.numeric(wt@W$W2))
    totV3 <- var(as.numeric(wt@W$W3))
    totV4 <-var(as.numeric(wt@W$W4))
    zz = data.frame(t=tbar, totV1, totV2, totV3, totV4)
    invisible(zz)
}


options(digits=20)
t = as.numeric(d$t)
m = as.numeric(d$mic)

zrain = rainmic(t,m)
