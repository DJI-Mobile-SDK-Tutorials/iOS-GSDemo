//
//  DJIMissionTrigger.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJIMissionControl.h"

NS_ASSUME_NONNULL_BEGIN



/**
 *  Mission Triggers can be used to trigger an action during the execution of a
 *  Timeline element if a set of criteria is met. The subclass of
 *  `DJIMissionTrigger` should implement the logic for collecting and judging the
 *  criteria, and then executing the action. Mission Triggers are  used in the
 *  Timeline element `DJIMissionControlTimelineElement`.
 *   Trigger actions can be listened to, so when subclassing this class,
 *  `notifyListenersOfEvent:error` should be used to notify listeners of trigger
 *  events.
 *  
 *  See Also: DJIMissionControl
 */
@interface DJIMissionTrigger : NSObject 


/**
 *  `YES` if the trigger is currently active. The trigger is active when the
 *  Timeline element it is associated with is being executed in the Timeline.
 */
@property BOOL isActive;


/**
 *  Begins trigger activity including monitoring the criteria required to  trigger
 *  the action. When subclassing, [super start]  should be called on the first line.
 */
- (void)start;


/**
 *  Ends all trigger activity including monitoring the criteria required to  trigger
 *  the action. When subclassing, [super stop]  should be called at the end.
 */
- (void)stop;


/**
 *  The type for the block being called when the trigger is triggered.
 */
typedef void (^DJIMissionTriggerAction)();


/**
 *  The action to execute. It is up to the trigger's implementation to decide when
 *  to call this action. The action should never be called by anything but the
 *  trigger. Actions can be implemented without using this property, but in addition
 *  `notifyListenersOfEvent:error` needs to be used to notify any listeners of the
 *  Trigger that an action was executed.
 *   In future subclasses of this property to be provided, this action  block will
 *  be used to give developers control of an action when a  set of criteria has been
 *  met. For example, a subclass of this may  be a battery threshold trigger. Once
 *  the battery passes some threshold developers will be able to define the action
 *  they want to trigger.
 */
@property (copy, nonatomic) DJIMissionTriggerAction action;

/*********************************************************************************/
#pragma mark - Listener
/*********************************************************************************/


/**
 *  Events that may occur during the lifecycle of a mission trigger.
 */
typedef NS_ENUM(NSInteger, DJIMissionTriggerEvent) {


    /**
     *  The default event if no other event matches the situation.
     */
    DJIMissionTriggerEventUnknown = -1,


    /**
     *  The trigger has started to monitor for its triggering criteria
     */
    DJIMissionTriggerEventStarted,


    /**
     *  The action block has been called as a result of matching the triggers' criteria
     */
    DJIMissionTriggerEventActionTriggered,


    /**
     *  The trigger no longer monitors data for its triggering criteria
     */
    DJIMissionTriggerEventStopped,
};


/**
 *  The block type used when an event is called and listened to.
 *  
 *  @param trigger The instance of the trigger
 *  @param event The event type which caused the block call
 *  @param error An optional error
 */
typedef void (^DJIMissionTriggerBlock)(DJIMissionTrigger *trigger, DJIMissionTriggerEvent event, NSError *_Nullable error);


/**
 *  Adds a listener to all trigger events with the passed block
 *  
 *  @param listener A listener object
 *  @param eventBlock A block to be called for each events
 */
- (void)addListener:(id)listener toTimelineProgressWithBlock:(DJIMissionTriggerBlock)eventBlock;


/**
 *  Removes the listener from the listeners pool of all trigger events.
 *  
 *  @param listener A previously added listener object.
 */
- (void)removeListener:(id)listener;


/**
 *  Removes all listeners from the listeners pool of all trigger events.
 */
- (void)removeAllListeners;


/**
 *  Notifies listeners about a trigger event. Should be used in subclasses
 *  especially after calling the action.
 *  
 *  @param event A valid DJIMissionTriggerEvent.
 *  @param error An optional error.
 */
- (void)notifyListenersOfEvent:(DJIMissionTriggerEvent)event
                         error:(NSError * _Nullable)error;

@end

NS_ASSUME_NONNULL_END
