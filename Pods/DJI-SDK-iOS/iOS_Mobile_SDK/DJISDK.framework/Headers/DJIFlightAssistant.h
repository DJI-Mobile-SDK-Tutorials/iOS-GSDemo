//
//  DJIFlightAssistant.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <DJISDK/DJIBaseProduct.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIFlightAssistant;
@class DJIVisionDetectionState;
@class DJIVisionControlState; 


/**
 *  This protocol provides an delegate method to update the Intelligent Flight
 *  Assistant current state.
 */
@protocol DJIFlightAssistantDelegate <NSObject>

@optional


/**
 *  Callback function that updates the vision detection state. The frequency of this
 *  method is 10Hz.
 *  
 *  @param assistant Intelligent flight assistant that has the updated state.
 *  @param state The state of vision sensor.
 */
- (void)flightAssistant:(DJIFlightAssistant *)assistant
     didUpdateVisionDetectionState:(DJIVisionDetectionState *)state;


/**
 *  Callback function that updates the aircraft state controlled by the intelligent
 *  flight assistant.
 *  
 *  @param assistant Intelligent flight assistant that has the updated state.
 *  @param state The control state.
 */
- (void)flightAssistant:(DJIFlightAssistant *)assistant
       didUpdateVisionControlState:(DJIVisionControlState *)state;

@end


/**
 *  This class contains components of the Intelligent Flight Assistant and provides
 *  methods to change its settings.
 */
@interface DJIFlightAssistant : NSObject


/**
 *  Intelligent flight assistant delegate.
 */
@property(nonatomic, weak) id<DJIFlightAssistantDelegate> delegate;


/**
 *  Enable collision avoidance. When enabled, the aircraft will stop and try to go
 *  around detected obstacles.
 *  
 *  @param enable A boolean value.
 *  @param completion Completion block that receives the execution result.
 */
- (void)setCollisionAvoidanceEnabled:(BOOL)enable
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets collision avoidance status (enabled/disabled).
 *  
 *  @param enable YES if collision avoidance is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getCollisionAvoidanceEnabledWithCompletion:(void (^_Nonnull)(BOOL enable, NSError *_Nullable error))completion;


/**
 *  Enables/disables precision landing. When enabled, the aircraft will record its
 *  take-off location visually  (as well as with GPS). On a Return-To-Home action
 *  the aircraft will attempt to perform a precision landing  using the additional
 *  visual information. This method only works on a Return-To-Home action when the
 *  home  location is successfully recorded during take-off, and not changed during
 *  flight.
 *  
 *  @param enabled `YES` to enable the precise landing.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setPrecisionLandingEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets precision landing status (enabled/disabled).
 *  
 *  @param enabled YES if precision landing is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPrecisionLandingEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables/disables landing protection. During auto-landing, the downwards facing
 *  vision sensor will check if  the ground surface is flat enough for a safe
 *  landing. If it is not and landing proteciton is enabled, then  landing will
 *  abort and need to be manually performed by the user.
 *  
 *  @param enabled `YES` to enable the landing protection.
 *  @param completion Completion block<<>android:Callback> that receives the setter result.
 */
- (void)setLandingProtectionEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets landing protection status (enabled/disabled).
 *  
 *  @param enabled YES if landing protection is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getLandingProtectionEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables/disables active obstacle avoidance. When enabled, and an obstacle is
 *  moving toward the aircraft,  the aircraft will actively fly away from it. If
 *  while actively avoiding a moving obstacle, the aircraft  detects another
 *  obstacle in its avoidance path, it will  stop.
 *  `setCollisionAvoidanceEnabled:withCompletion` must also be enabled.
 *  
 *  @param enabled `YES` to enable the active avoidance.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setActiveObstacleAvoidanceEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets active obstacle avoidance status (enabled/disabled).
 *  
 *  @param enabled YES if active obstacle avoidance is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getActiveObstacleAvoidanceEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables/disables upward avoidance. When the Inspire 2's upwards-facing infrared
 *  sensor detects an obstacle, the  aircraft will slow its ascent and maintain a
 *  minimum distance of 1 meter from the obstacle. The  sensor has a 10-degree
 *  horizontal field of view (FOV) and 10-degree vertical FOV. The maximum detection
 *  distance is 5m.
 *  
 *  @param enabled `YES` to enable the upwards avoidance.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setUpwardsAvoidanceEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets upward avoidance status (enabled/disabled).
 *  
 *  @param enabled YES if upwards avoidance is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getUpwardsAvoidanceEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
