//
// Created by jerett on 2018-12-24.
//

/**
 *  implement opencv staple tracker.
 */


#pragma once

#include <opencv2/tracking.hpp>
#include "staple/staple_tracker.h"
#include "MosseTracker.h"


namespace cd {

class Tracker {

public:
    enum Algorithm {
        Boosting,
        KCF,
        MIL,
        TLD,
        MedianFlow,
        GOTURN,
        MOSSE,
        OpenCVMOSSE,
        Staple,
    };

    static cv::Ptr<Tracker> Create(Algorithm algorithm);
    virtual ~Tracker() = default;
    virtual bool Init(cv::Mat &frame, const cv::Rect2d &box) = 0;
    virtual bool Update(cv::Mat &frame, cv::Rect2d &out_box) = 0;
};


class TrackerOpenCV : public Tracker {
public:
    explicit TrackerOpenCV(Algorithm algorithm);
    virtual ~TrackerOpenCV() = default;

    bool Init(cv::Mat &frame, const cv::Rect2d &box) override;
    bool Update(cv::Mat &frame, cv::Rect2d &out_box) override;

private:
    cv::Ptr<cv::Tracker> tracker_;
};

class TrackerMOSSE : public Tracker {
public:
    explicit TrackerMOSSE() {
        ;
    }
    virtual ~TrackerMOSSE() = default;

    bool Init(cv::Mat& frame, const cv::Rect2d& box) override {
        return tracker_.Init(frame, box);
    }

    bool Update(cv::Mat& frame, cv::Rect2d& out_box) override {
        return tracker_.Update(frame, out_box);
    }

private:
    MOSSETracker tracker_;
};

class TrackerStaple : public Tracker {
public:
    explicit TrackerStaple();
    virtual ~TrackerStaple() = default;

    bool Init(cv::Mat &frame, const cv::Rect2d &box) override;
    bool Update(cv::Mat &frame, cv::Rect2d &out_box) override;

private:
    STAPLE_TRACKER tracker_;
};

}


