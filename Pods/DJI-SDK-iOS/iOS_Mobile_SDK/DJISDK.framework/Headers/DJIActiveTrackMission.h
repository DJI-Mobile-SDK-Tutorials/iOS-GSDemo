//
//  DJIActiveTrackMission.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#ifndef DJIActiveTrackMission_h
#define DJIActiveTrackMission_h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "DJIMission.h"


/**
 *  The state of the target being tracked by the aircraft.
 */
typedef NS_ENUM(NSInteger, DJIActiveTrackTargetState) {

    /**
     *  The aircraft has recognized the target but the user is not allowed to confirm
     *  the target. Check `cannotConfirmReason` to get  more information.
     */
    DJIActiveTrackTargetStateCannotConfirm,

    /**
     *  The aircraft has recognized the target and is waiting for user's confirmation.
     *  If this state, the aircraft will hover in the current position while the camera
     *  is tracking the target (by rotating aircraft's yaw or gimbal's altitude). If
     *  user confirms the target, the aircraft will start to following the movement of
     *  the target.
     */
    DJIActiveTrackTargetStateWaitingForConfirmation,

    /**
     *  The aircraft has recognized the target with high confidence.
     */
    DJIActiveTrackTargetStateTrackingWithHighConfidence,

    /**
     *  The ActiveTrack Mission is tracking a target with low confidence. This is only
     *  an indication that either the aircraft will soon ask for confirmation that the
     *  target is correct, or may loose tracking the target entirely if confidence
     *  doesn't improve.
     */
    DJIActiveTrackTargetStateTrackingWithLowConfidence,

    /**
     *  Unknown.
     */
    DJIActiveTrackTargetStateUnknown = 0xFF
};


/**
 *  The type of ActiveTrack target.
 */
typedef NS_ENUM(NSInteger, DJIActiveTrackTargetType) {

    /**
     *  The ActiveTrack target is a human being.
     */
    DJIActiveTrackTargetTypeHuman,

    /**
     *  The ActiveTrack target is a car.
     */
    DJIActiveTrackTargetTypeCar,

    /**
     *  The ActiveTrack target is a van.
     */
    DJIActiveTrackTargetTypeVan,

    /**
     *  The ActiveTrack target is a bike.
     */
    DJIActiveTrackTargetTypeBike,

    /**
     *  The ActiveTrack target is a boat.
     */
    DJIActiveTrackTargetTypeBoat,

    /**
     *  The aircraft cannot recognize the target type.
     */
    DJIActiveTrackTargetTypeUnknown
};


/**
 *  Different modes of the ActiveTrack Mission. Defaults to
 *  `DJIActiveTrackModeTrace`, set to  others to enable the feature.
 */
typedef NS_ENUM (NSInteger, DJIActiveTrackMode) {


    /**
     *  Aircraft moves in behind the subject keeping a constant distance to it.  Mission
     *  with this mode can only be started when the aircraft is flying.
     */
    DJIActiveTrackModeTrace,


    /**
     *  Aircraft moves in parallel with the subject in the frame instead of behind.
     *  Mission with this mode can only be started when the aircraft is flying.
     */
    DJIActiveTrackModeProfile,


    /**
     *  In Spotlight mode, the aircraft camera automatically follows the subject by
     *  rotating the aircraft's yaw, but the aircraft does not automatically keep a
     *  constant distance with the subject. Mission with this mode can only be started
     *  when the aircraft is flying.
     */
    DJIActiveTrackModeSpotlight,


    /**
     *  In Spotlight Pro mode, the aircraft camera automatically follows the subject by
     *  rotating the gimbal's yaw, but the aircraft does not automatically keep a
     *  constant  distance with the subject.
     */
    DJIActiveTrackModeSpotlightPro,


    /**
     *  The active track mode is unknown.
     */
    DJIActiveTrackModeUnknown = 0xFF
};


/**
 *  The reason why user is not allowed to confirm the current target.
 */
typedef NS_ENUM (NSInteger, DJIActiveTrackCannotConfirmReason) {

    /**
     *  None.
     */
    DJIActiveTrackCannotConfirmReasonNone,

    /**
     *  The target is unstable.
     */
    DJIActiveTrackCannotConfirmReasonUnstableTarget,

    /**
     *  The target position is too high.
     */
    DJIActiveTrackCannotConfirmReasonTargetTooHigh,

    /**
     *  There is an obstacle between the aircraft and the target that is blocking the
     *  target.
     */
    DJIActiveTrackCannotConfirmReasonBlockedByObstacle,

    /**
     *  The gimbal's attitude is pointing to the ground.
     */
    DJIActiveTrackCannotConfirmReasonGimbalAttitudeError,

    /**
     *  The target is too far away from the aircraft.
     */
    DJIActiveTrackCannotConfirmReasonTargetTooFar,

    /**
     *  The target is too close to the aircraft.
     */
    DJIActiveTrackCannotConfirmReasonTargetTooClose,

    /**
     *  The altitude of the aircraft is too high.
     */
    DJIActiveTrackCannotConfirmReasonAircraftTooHigh,

    /**
     *  The altitude of the aircraft is too low.
     */
    DJIActiveTrackCannotConfirmReasonAircraftTooLow,

    /**
     *  The obstacle vision sensor has errors.
     */
    DJIActiveTrackCannotConfirmReasonObstacleSensorError,

    /**
     *  Unknown.
     */
    DJIActiveTrackCannotConfirmReasonUnknown = 0xFF
};


/**
 *  The tracking state of the ActiveTrack mission that is executing.
 */
@interface DJIActiveTrackTrackingState : NSObject

/**
 *  The state of the  being tracked.
 */
@property (nonatomic, readonly) DJIActiveTrackTargetState state;

/**
 *  The type of the target being tracked.
 */
@property (nonatomic, readonly) DJIActiveTrackTargetType targetType;


/**
 *  A rectangle in the live video view image that represents the target being
 *  tracked.  The rectangle is normalized to [0,1] where (0,0) is the top left of
 *  the video  preview and (1,1) is the bottom right.
 *  
 *  @return .
 */
@property (nonatomic, readonly) CGRect targetRect;


/**
 *  Reason why the target cannot be confirmed by the user. It is useful when
 *  `state` is  `DJIActiveTrackTargetStateCannotConfirm`.  Otherwise, it is
 *  `DJIActiveTrackCannotConfirmReasonNone`.
 */
@property (nonatomic, readonly) DJIActiveTrackCannotConfirmReason cannotConfirmReason;

@end


/**
 *  ActiveTrack Mission allows an aircraft to track a moving subject using the
 *  vision system and without a GPS tracker on the subject.
 */
@interface DJIActiveTrackMission : DJIMission

/**
 *  A bounding box for the target. The rectangle is normalized to [0,1] where (0,0)
 *  is the top left of the video preview and (1,1) is the bottom right. The `size`
 *  parameter of `CGRect` can be set to 0 to initialize the mission with a point
 *  instead of a rectangle. If the mission is initialized with a point, the vision
 *  system will try to recognize the object around the point and return the
 *  representative  rect in the status delegate.
 */
@property (nonatomic, readwrite) CGRect targetRect;


/**
 *  ActiveTrack Mission mode. Defaults to `DJIActiveTrackModeTrace`.
 */
@property (nonatomic, readwrite) DJIActiveTrackMode mode;

@end

#endif /* DJIActiveTrackMission_h */
