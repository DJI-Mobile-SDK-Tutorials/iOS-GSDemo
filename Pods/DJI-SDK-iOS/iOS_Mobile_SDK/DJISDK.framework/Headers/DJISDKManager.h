//
//  DJISDKManager.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  To register the app, create a new key in the info.plist file where the plist key
 *  is "DJISDKAppKey" and its value is your DJI registered App key.
 */
#define SDK_APP_KEY_INFO_PLIST_KEY @"DJISDKAppKey"

NS_ASSUME_NONNULL_BEGIN
@class DJIAircraft;
@class DJIBaseProduct;
@class DJIBaseComponent;
@class DJIBluetoothProductConnector;
@class DJIKeyManager;
@class DJIFlyZoneManager;
@class DJIMissionControl;
@class DJIDiagnosticsManager;
@class DJIVideoFeeder;


/**
 *  This protocol provides delegate methods to receive the updated registration
 *  status and the change of the  connected product.
 */
@protocol DJISDKManagerDelegate <NSObject>

@required


/**
 *  Delegate method after the application attempts to register.
 *  
 *  @param error `nil` if registration is successful. Otherwise it contains an `NSError` object with error codes from `DJISDKRegistrationError`.
 */
- (void)appRegisteredWithError:(NSError *_Nullable)error;

@optional


/**
 *  Called when the "product" is connected.
 *  
 *  @param product Product object. nil if the USB link or WiFi link between the product and phone is  disconnected.
 */
- (void)productConnected:(DJIBaseProduct *_Nullable)product;


/**
 *  Called when the "product" is disconnected.
 */
- (void)productDisconnected;


/**
 *  Called when the "component" is connected.
 *  
 *  @param key Key of the component.
 *  @param index Index of the component.
 */
- (void)componentConnectedWithKey:(NSString * _Nullable)key andIndex:(NSInteger)index;


/**
 *  Called when the "component" is disconnected.
 *  
 *  @param key Key of the component.
 *  @param index Index of the component.
 */
- (void)componentDisconnectedWithKey:(NSString * _Nullable)key andIndex:(NSInteger)index;

@end


/**
 *  This protocol provides delegate methods to receive the updated connection status
 *  between the debug server,  remote controller and debug client.
 */
@protocol BridgeAppServerDelegate <NSObject>

@optional


/**
 *  Callback delegate method after the Debug server is started.
 *  
 *  @param isRCConnected `YES` if the RC is connected with the Debug server.
 *  @param isWifiConnected `YES` if the debug client is connected with the Debug server based on WiFi.
 */
- (void)bridgeAppServerWithRCConnectionStatus:(BOOL)isRCConnected andDebugClientConnectionStatus:(BOOL)isWifiConnected;

@end


/**
 *  This class is the entry point for using the SDK with a DJI product.  Most
 *  importantly, this class is used to register the SDK, and to connect  to and
 *  access the product. This class also provides access to important feature
 *  managers (such as `keyManager`), debugging tools, and threading control of
 *  asynchronous completion blocks. SDK Registration using `registerAppWithDelegate`
 *  must be successful before the SDK can be used with a DJI product.
 */
@interface DJISDKManager : NSObject


/**
 *  The DJI product which is connected to the mobile device, only available after
 *  successful registration of the app.
 *  
 *  @return A instance of `DJIBaseProduct`.
 */
+ (__kindof DJIBaseProduct *_Nullable)product;



/**
 *  Used to establish the Bluetooth connection between the mobile device and the DJI
 *  product. The Bluetooth connection needs to be established before a connection
 *  between the SDK and the DJI product can be made using
 *  `startConnectionToProduct`.
 *  
 *  @return A `DJIBluetoothProductConnector` instance.
 */
+ (nullable DJIBluetoothProductConnector *)bluetoothProductConnector;


/**
 *  The first time the app is initialized after installation, the app connects to a
 *  DJI Server through the  internet to verify the Application Key. Subsequent app
 *  starts will use locally cached verification  information to register the app.
 *  
 *  @param delegate Delegate used for both the registration result, and when the product changes.
 */
+ (void)registerAppWithDelegate:(id<DJISDKManagerDelegate>)delegate;


/**
 *  Queue in which completion blocks are called. If left unset,  completion blocks
 *  are called in main queue.
 *  
 *  @param completionBlockQueue Dispatch queue.
 */
+ (void)setCompletionBlockQueue:(dispatch_queue_t)completionBlockQueue;


/**
 *  Some products (e.g. Mavic Pro, Inspire 2, Phantom 4 Pro) make use of both 2.4
 *  GHz and 5 GHz spectrums for wireless communication. While 5 GHz will not
 *  necessarily have the same range as 2.4 GHz, it can be useful  if the 2.4 GHz
 *  band has a lot of existing interference. However, as some countries do not
 *  permit the use of the 5 GHz spectrum, the SDK will automatically try to
 *  determine the country in which the product is operating and enable or disable
 *  the 5 GHz option accordingly. The process of determining in which country the
 *  product is flying uses location information. This method can be used to disable
 *  this check, but must  be called before `registerAppWithDelegate` to take effect.
 *  If  disabled, only 2.4 GHz will be available as an option.
 *  
 *  @param disableCountryCodeCheck `YES` if the country code check is disabled.
 */
+ (void)setDisableCountryCodeCheck:(BOOL)disableCountryCodeCheck;


/**
 *  Starts a connection between the SDK and the DJI product. This method should be
 *  called  after successful registration of the app and once there is a data
 *  connection between the mobile device and DJI product. This data connection is
 *  either a USB cable connection, a WiFi connection (that needs to be established
 *  outside of the SDK) or a Bluetooth connection (that needs to be established with
 *  `bluetoothProductConnector`). If the connection succeeds, `productConnected`
 *  will be called if the connection succeeded. Returns `YES` if the connection is
 *  started successfully. For products which connect to the mobile device using
 *  Bluetooth, `bluetoothProductConnector` should be used to get a
 *  `DJIBluetoothProductConnector` object which can handle Bluetooth device
 *  connection.
 *  
 *  @return `YES` if the connection is started successfully.
 */
+ (BOOL)startConnectionToProduct;


/**
 *  Disconnect from the connected DJI product.
 */
+ (void)stopConnectionToProduct;


/**
 *  Set the SDK to close the connection automatically when the app enters the
 *  background, and resume connection  automatically when the app enters the
 *  foreground. Default is `YES`.
 *  
 *  @param isClose `YES` if the connection should be closed when entering background.
 */
+ (void)closeConnectionWhenEnteringBackground:(BOOL)isClose;


/**
 *  Gets the DJI Mobile SDK Version. Returns SDK version as a string.
 *  
 *  @return An NSString object.
 */
+ (NSString *)SDKVersion;


/**
 *  Registration state.
 *  
 *  @return `YES` if SDK is registered.
 */
+ (BOOL)hasSDKRegistered;


/**
 *  Enter debug mode with debug IP.
 *  
 *  @param bridgeAppIP Debug IP of the DJI Bridge App.
 */
+ (void)enableBridgeModeWithBridgeAppIP:(NSString *)bridgeAppIP;


/**
 *  Enable remote logging with log server URL.
 *  
 *  @param deviceID Optional device ID to uniquely identify logs from an installation.
 *  @param url URL of the remote log server.
 */
+ (void)enableRemoteLoggingWithDeviceID:(NSString *_Nullable)deviceID logServerURLString:(NSString *)url;


/**
 *  The DJI Mobile SDK collects logs that are related to flight. These logs can be
 *  used to help diagnose the cause  of a product's flight failure at the SDK and
 *  mobile application layers. They are predominantly used by a DJI  service
 *  facility, who will combine them with the product's flight logs (stored on the
 *  product) to better  understand the root cause of a crash and determine whether
 *  the incident is covered under warranty. They can  also be used by developers to
 *  debug their application. SDK Logs record commands from the application to the
 *  SDK, and information from the SDK to the application that are related to flight.
 *  Logs are cached to the mobile  device, and will overwrite themselves to limit
 *  storage footprint. `archiveLogs` will move the logs to an archive  folder. Logs
 *  in the archive, will only be overwritten by newer archives that go beyond the
 *  storage limit and not  normal log generation. The storage limit for normal log
 *  generation is 400 MB (about 500 minutes of flight). The  storage limit for the
 *  archive is an additional 400 MB. The logs have an encrypted and unencrypted
 *  portion. The  unencrypted portion can be used by developers to see all commands
 *  and information sent to and received from the  SDK by the mobile application
 *  that is related to flight. The encrypted portion can only be used by a DJI
 *  service  facility as it includes proprietary hardware protocols and is used to
 *  tie the SDK logs and product flight logs  together. Logs can be transferred to
 *  the DJI service facility either by manually downloading from the mobile  device
 *  using iTunes, or the application can send archived logs to a DJI endpoint using
 *  `uploadArchivedLogs`.  Developers should be careful to upload logs directly when
 *  the user is on a cellular connection as the archive  can be up to 400 MB. Return
 *  path of archived logs, nil if a problem occurred.
 *  
 *  @return An NSString object for the archive logs.
 */
+ (nullable NSString *)archiveLogs;


/**
 *  Upload the archive to DJI. The archive will not be deleted when calling this
 *  method.
 */
+ (void)uploadArchivedLogs;

/*********************************************************************************/
#pragma mark - Keyed Interface
/*********************************************************************************/


/**
 *  Provide access to the SDK Key interface.
 *  
 *  @return An instance of `DJIKeyManager`.
 */
+ (nullable DJIKeyManager *)keyManager;

/*********************************************************************************/
#pragma mark - Fly Zone Manager
/*********************************************************************************/


/**
 *  Provide access to `DJIFlyZoneManager` used to manage DJI's GEO system for no fly
 *  zones.
 *  
 *  @return An instance of `DJIFlyZoneManager`.
 */
+ (nullable DJIFlyZoneManager *)flyZoneManager;

/*********************************************************************************/
#pragma mark - Mission Control
/*********************************************************************************/


/**
 *  Provide access to `DJIMissionControl` used to manage missions.
 *  
 *  @return An instance of `DJIMissionControl`.
 */
+ (nullable DJIMissionControl *)missionControl;

/*********************************************************************************/
#pragma mark - Video Feeder
/*********************************************************************************/


/**
 *  Provide access to `DJIVideoFeeder` used to video feeder.
 *  
 *  @return An instance of `DJIVideoFeeder`.
 */
+ (nullable DJIVideoFeeder *)videoFeeder;

@end

/*********************************************************************************/
#pragma mark - DJISDKManager (DebugServer)
/*********************************************************************************/

/**
 *  This class provides methods for you to start and stop the SDK debug server.
 *  You can use them with the DJI Bridge App for remote debugging.
 */
@interface DJISDKManager (DebugServer)


/**
 *  Start the debug server. Note, this method is only used if building  the Bridge
 *  App application and should not be used in a typical application.
 *  
 *  @param ipaddress The IP address string.
 *  @param block block returns the IP address of the server.
 */
+ (void)startBridgeAppServerWithCompletion:(void (^)(NSString *ipaddress))block;


/**
 *  Register the delegate object to get the connection status of the debug server
 *  with the Remote controller and the debug client. Note, this  method is only used
 *  if building the Bridge App application and should not be used in a typical
 *  application.
 *  
 *  @param delegate DJISDKDebugServerDelegate object.
 */
+ (void)setBridgeAppServerDelegate:(id <BridgeAppServerDelegate>)delegate;


/**
 *  Stop the debug server and release the service objects used by the server. Note,
 *  this method is only used if building the Bridge App application  and should not
 *  be used in a typical application.
 */
+ (void)stopSDKDebugServer;

@end

NS_ASSUME_NONNULL_END
