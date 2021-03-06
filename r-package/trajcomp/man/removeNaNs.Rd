% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/Tools.R
\name{removeNaNs}
\alias{removeNaNs}
\title{Remove separating NaN lines from a dataset}
\usage{
removeNaNs(S)
}
\arguments{
\item{x}{A trajectory database separated by NaN lines}
}
\value{
The same object without NaN lines
}
\description{
Remove separating NaN lines from a dataset
}
\examples{
removeNaNs(prague);
}
\seealso{
Other basic trajectory dataset tools: \code{\link{getTrajectoryIDs}},
  \code{\link{tsplit}}
}

