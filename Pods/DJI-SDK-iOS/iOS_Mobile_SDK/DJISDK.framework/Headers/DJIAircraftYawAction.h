//
//  DJIAircraftYawAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The error domain used to describe errors produced by the `DJIAircraftYawAction`
 *  object.
 */
extern const NSErrorDomain DJIAircraftYawActionErrorDomain;


/**
 *  Error codes for errors specific to `DJIAircraftYawActionErrorDomain`.
 */
typedef NS_ENUM(NSInteger, DJIAircraftYawActionError) {

    /**
     *  Default value when no other value is appropriate.
     */
    DJIAircraftYawActionErrorUnknown = -1,
    

    /**
     *  Set rotation speed is not within valid range [0, 100].
     */
    DJIAircraftYawActionErrorInvalidRotationSpeed = 100,
    

    /**
     *  Set angle value is not within valid range [-180, 180].
     */
    DJIAircraftYawActionErrorInvalidAngleValue = 101,
};


/**
 *  This class represents an aircraft yaw rotation action to be scheduled on the
 *  Mission  Control timeline. By creating an object of this class and adding it to
 *  the timeline,  an aircraft will rotate around yaw by the specified angle with
 *  the specified speed  when the Timeline reaches the action.
 */
@interface DJIAircraftYawAction : DJIMissionAction


/**
 *  Initialize with a yaw angle relative to current heading and an angular velocity.
 *  The angular velocity has a range of [0, 100] degrees/s and a default value of 20
 *  degrees/s.
 *  
 *  @param angle Angle in degrees.
 *  @param velocity Velocity in degrees/s.
 *  
 *  @return An instance of `DJIAircraftYawAction`.
 */
- (instancetype _Nullable)initWithRelativeAngle:(double)angle andAngularVelocity:(double)velocity;

@end

NS_ASSUME_NONNULL_END
