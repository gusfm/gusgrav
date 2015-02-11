#include "gtest/gtest.h"
#include "point2d.h"

class Point2dTest : public testing::Test {
    protected:
        virtual void SetUp() {
            point_ = new Point2d(0.0, 0.0);
        }
        virtual void TearDown() {
            delete point_;
        }
        Point2d *point_;
};

TEST_F(Point2dTest, basic) {
    /* Empty test */
}

TEST_F(Point2dTest, methods) {
    EXPECT_EQ(0.0, point_->get_x());
    EXPECT_EQ(0.0, point_->get_y());
}
