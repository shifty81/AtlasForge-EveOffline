#include "../engine/graphvm/GraphTimeline.h"
#include <iostream>
#include <cassert>

using namespace atlas::graphvm;

void test_timeline_empty() {
    GraphTimeline timeline;
    assert(timeline.FrameCount() == 0);
    assert(timeline.CurrentFrame() == nullptr);
    assert(!timeline.StepForward());
    assert(!timeline.StepBackward());
    auto [first, last] = timeline.TickRange();
    assert(first == 0 && last == 0);
    std::cout << "[PASS] test_timeline_empty" << std::endl;
}

void test_timeline_record_frame() {
    GraphTimeline timeline;
    GraphSnapshot snap;
    snap.nodes.push_back({1, "Noise"});

    timeline.RecordFrame(10, snap, "Frame A");
    assert(timeline.FrameCount() == 1);
    assert(timeline.CurrentFrame() != nullptr);
    assert(timeline.CurrentFrame()->tick == 10);
    assert(timeline.CurrentFrame()->label == "Frame A");
    assert(timeline.CurrentFrame()->snapshot.nodes.size() == 1);
    std::cout << "[PASS] test_timeline_record_frame" << std::endl;
}

void test_timeline_seek() {
    GraphTimeline timeline;
    GraphSnapshot snap1, snap2, snap3;
    snap1.nodes.push_back({1, "A"});
    snap2.nodes.push_back({1, "A"});
    snap2.nodes.push_back({2, "B"});
    snap3.nodes.push_back({1, "A"});
    snap3.nodes.push_back({2, "B"});
    snap3.nodes.push_back({3, "C"});

    timeline.RecordFrame(1, snap1);
    timeline.RecordFrame(2, snap2);
    timeline.RecordFrame(3, snap3);

    assert(timeline.CurrentIndex() == 2); // last recorded
    assert(timeline.SeekTo(0));
    assert(timeline.CurrentIndex() == 0);
    assert(timeline.CurrentFrame()->tick == 1);
    assert(!timeline.SeekTo(99)); // out of bounds
    std::cout << "[PASS] test_timeline_seek" << std::endl;
}

void test_timeline_step() {
    GraphTimeline timeline;
    GraphSnapshot snap;

    timeline.RecordFrame(1, snap);
    timeline.RecordFrame(2, snap);
    timeline.RecordFrame(3, snap);

    timeline.SeekToBeginning();
    assert(timeline.CurrentIndex() == 0);
    assert(timeline.StepForward());
    assert(timeline.CurrentIndex() == 1);
    assert(timeline.StepForward());
    assert(timeline.CurrentIndex() == 2);
    assert(!timeline.StepForward()); // at end

    assert(timeline.StepBackward());
    assert(timeline.CurrentIndex() == 1);
    assert(timeline.StepBackward());
    assert(timeline.CurrentIndex() == 0);
    assert(!timeline.StepBackward()); // at beginning
    std::cout << "[PASS] test_timeline_step" << std::endl;
}

void test_timeline_seek_to_end() {
    GraphTimeline timeline;
    GraphSnapshot snap;

    timeline.RecordFrame(1, snap);
    timeline.RecordFrame(2, snap);
    timeline.RecordFrame(3, snap);

    timeline.SeekToBeginning();
    assert(timeline.CurrentIndex() == 0);

    timeline.SeekToEnd();
    assert(timeline.CurrentIndex() == 2);
    std::cout << "[PASS] test_timeline_seek_to_end" << std::endl;
}

void test_timeline_diff_to_next() {
    GraphTimeline timeline;

    GraphSnapshot snap1;
    snap1.nodes.push_back({1, "A"});

    GraphSnapshot snap2;
    snap2.nodes.push_back({1, "A"});
    snap2.nodes.push_back({2, "B"});

    timeline.RecordFrame(1, snap1);
    timeline.RecordFrame(2, snap2);

    timeline.SeekToBeginning();
    auto diff = timeline.DiffToNext();
    assert(diff.HasChanges());
    assert(diff.nodeDiffs.size() == 1);
    assert(diff.nodeDiffs[0].action == DiffAction::Added);
    assert(diff.nodeDiffs[0].nodeId == 2);

    // At last frame, diff to next is empty
    timeline.SeekToEnd();
    auto emptyDiff = timeline.DiffToNext();
    assert(!emptyDiff.HasChanges());
    std::cout << "[PASS] test_timeline_diff_to_next" << std::endl;
}

void test_timeline_diff_from_previous() {
    GraphTimeline timeline;

    GraphSnapshot snap1;
    snap1.nodes.push_back({1, "A"});

    GraphSnapshot snap2;
    snap2.nodes.push_back({1, "A"});
    snap2.nodes.push_back({2, "B"});

    timeline.RecordFrame(1, snap1);
    timeline.RecordFrame(2, snap2);

    // At second frame, diff from previous shows what was added
    assert(timeline.CurrentIndex() == 1);
    auto diff = timeline.DiffFromPrevious();
    assert(diff.HasChanges());
    assert(diff.nodeDiffs.size() == 1);
    assert(diff.nodeDiffs[0].action == DiffAction::Added);

    // At first frame, diff from previous is empty
    timeline.SeekToBeginning();
    auto emptyDiff = timeline.DiffFromPrevious();
    assert(!emptyDiff.HasChanges());
    std::cout << "[PASS] test_timeline_diff_from_previous" << std::endl;
}

void test_timeline_tick_range() {
    GraphTimeline timeline;
    GraphSnapshot snap;

    timeline.RecordFrame(5, snap);
    timeline.RecordFrame(10, snap);
    timeline.RecordFrame(20, snap);

    auto [first, last] = timeline.TickRange();
    assert(first == 5);
    assert(last == 20);
    std::cout << "[PASS] test_timeline_tick_range" << std::endl;
}

void test_timeline_clear() {
    GraphTimeline timeline;
    GraphSnapshot snap;

    timeline.RecordFrame(1, snap);
    timeline.RecordFrame(2, snap);
    assert(timeline.FrameCount() == 2);

    timeline.Clear();
    assert(timeline.FrameCount() == 0);
    assert(timeline.CurrentFrame() == nullptr);
    std::cout << "[PASS] test_timeline_clear" << std::endl;
}

void test_timeline_get_frame_at_tick() {
    GraphTimeline timeline;
    GraphSnapshot snap;
    snap.nodes.push_back({1, "A"});

    timeline.RecordFrame(10, snap);
    timeline.RecordFrame(20, snap);

    auto* frame = timeline.GetFrameAtTick(10);
    assert(frame != nullptr);
    assert(frame->tick == 10);

    auto* missing = timeline.GetFrameAtTick(15);
    assert(missing == nullptr);
    std::cout << "[PASS] test_timeline_get_frame_at_tick" << std::endl;
}
