//
//  DJIRootViewController.m
//  GSDemo
//
//  Created by OliverOu on 7/7/15.
//  Copyright (c) 2015 DJI. All rights reserved.
//

#import "DJIRootViewController.h"
#import "DJIGSButtonViewController.h"
#import "DJIWaypointConfigViewController.h"

#define kEnterNaviModeFailedAlertTag 1001

@interface DJIRootViewController ()<DJIGSButtonViewControllerDelegate, DJIWaypointConfigViewControllerDelegate>
@property (nonatomic, assign)BOOL isEditingPoints;
@property (nonatomic, strong)DJIGSButtonViewController *gsButtonVC;
@property (nonatomic, strong)DJIWaypointConfigViewController *waypointConfigVC;
@end

@implementation DJIRootViewController

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self startUpdateLocation];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];

    [self.locationManager stopUpdatingLocation];

    [self.inspireDrone.mainController stopUpdateMCSystemState];
    [self.inspireDrone disconnectToDrone];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    [self initUI];
    [self initData];
    [self initDrone];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return NO;
}

#pragma mark NSNotification Selector Method
- (void)registerAppSuccess:(NSNotification *)notification
{
    [self.inspireDrone connectToDrone];
    [self.inspireMainController startUpdateMCSystemState];
}

#pragma mark Init Methods
-(void)initData
{
    self.userLocation = kCLLocationCoordinate2DInvalid;
    self.droneLocation = kCLLocationCoordinate2DInvalid;
    
    self.mapController = [[DJIMapController alloc] init];
    self.tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(addWaypoints:)];
    [self.mapView addGestureRecognizer:self.tapGesture];

}

-(void) initUI
{
    self.modeLabel.text = @"N/A";
    self.gpsLabel.text = @"0";
    self.vsLabel.text = @"0.0 M/S";
    self.hsLabel.text = @"0.0 M/S";
    self.altitudeLabel.text = @"0 M";
    
    self.gsButtonVC = [[DJIGSButtonViewController alloc] initWithNibName:@"DJIGSButtonViewController" bundle:[NSBundle mainBundle]];
    [self.gsButtonVC.view setFrame:CGRectMake(0, self.topBarView.frame.origin.y + self.topBarView.frame.size.height, self.gsButtonVC.view.frame.size.width, self.gsButtonVC.view.frame.size.height)];
    self.gsButtonVC.delegate = self;
    [self.view addSubview:self.gsButtonVC.view];
    
    self.waypointConfigVC = [[DJIWaypointConfigViewController alloc] initWithNibName:@"DJIWaypointConfigViewController" bundle:[NSBundle mainBundle]];
    self.waypointConfigVC.view.alpha = 0;
    self.waypointConfigVC.view.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleBottomMargin;
    
    CGFloat configVCOriginX = (CGRectGetWidth(self.view.frame) - CGRectGetWidth(self.waypointConfigVC.view.frame))/2;
    CGFloat configVCOriginY = CGRectGetHeight(self.topBarView.frame) + CGRectGetMinY(self.topBarView.frame) + 8;
    
    [self.waypointConfigVC.view setFrame:CGRectMake(configVCOriginX, configVCOriginY, CGRectGetWidth(self.waypointConfigVC.view.frame), CGRectGetHeight(self.waypointConfigVC.view.frame))];
    
    if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) //Check if it's using iPad and center the config view
    {
        self.waypointConfigVC.view.center = self.view.center;
    }

    self.waypointConfigVC.delegate = self;
    [self.view addSubview:self.waypointConfigVC.view];
    
}

- (void)initDrone
{
    self.inspireDrone = [[DJIDrone alloc] initWithType:DJIDrone_Inspire];
    self.inspireDrone.delegate = self;
    
    self.navigationManager = self.inspireDrone.mainController.navigationManager;
    self.navigationManager.delegate = self;
    
    self.inspireMainController = (DJIInspireMainController*)self.inspireDrone.mainController;
    self.inspireMainController.mcDelegate = self;
    
    self.waypointMission = self.navigationManager.waypointMission;
    
    [self registerApp];
}

- (void)registerApp
{
    NSString *appKey = @"337d68bbd8afb5cc7700b1a1";
    [DJIAppManager registerApp:appKey withDelegate:self];
}

- (void)focusMap
{
    if (CLLocationCoordinate2DIsValid(self.droneLocation)) {
        MKCoordinateRegion region = {0};
        region.center = self.droneLocation;
        region.span.latitudeDelta = 0.001;
        region.span.longitudeDelta = 0.001;
        
        [self.mapView setRegion:region animated:YES];
    }
    
}

-(void) hideProgressView
{
    if (self.uploadProgressView) {
        [self.uploadProgressView dismissWithClickedButtonIndex:-1 animated:YES];
        self.uploadProgressView = nil;
    }
}

#pragma mark DJIAppManagerDelegate Method
-(void)appManagerDidRegisterWithError:(int)error
{
    NSString* message = @"Register App Successed!";
    if (error != RegisterSuccess) {
        message = @"Register App Failed! Please enter your App Key and check the network.";
    }else
    {
        [self.inspireDrone connectToDrone];
        [self.inspireDrone.mainController startUpdateMCSystemState];
    }
    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Register App" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alertView show];
}

#pragma mark CLLocation Methods
-(void) startUpdateLocation
{
    if ([CLLocationManager locationServicesEnabled]) {
        if (self.locationManager == nil) {
            self.locationManager = [[CLLocationManager alloc] init];
            self.locationManager.delegate = self;
            self.locationManager.desiredAccuracy = kCLLocationAccuracyBest;
            self.locationManager.distanceFilter = 0.1;
            if ([self.locationManager respondsToSelector:@selector(requestAlwaysAuthorization)]) {
                [self.locationManager requestAlwaysAuthorization];
            }
            [self.locationManager startUpdatingLocation];
        }
    }else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Location Service is not available" message:@"" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
    }
}

#pragma mark UITapGestureRecognizer Methods
- (void)addWaypoints:(UITapGestureRecognizer *)tapGesture
{
    CGPoint point = [tapGesture locationInView:self.mapView];
    
    if(tapGesture.state == UIGestureRecognizerStateEnded){

        if (self.isEditingPoints) {
            [self.mapController addPoint:point withMapView:self.mapView];
        }
        
    }

}

#pragma mark - DJINavigationDelegate

-(void) onNavigationMissionStatusChanged:(DJINavigationMissionStatus*)missionStatus
{
    
}

#pragma mark - GroundStationDelegate

-(void) groundStation:(id<DJIGroundStation>)gs didExecuteWithResult:(GroundStationExecuteResult*)result
{
    if (result.currentAction == GSActionStart) {
        if (result.executeStatus == GSExecStatusFailed) {
            [self hideProgressView];
            NSLog(@"Mission Start Failed...");
        }
    }
    if (result.currentAction == GSActionUploadTask) {
        if (result.executeStatus == GSExecStatusFailed) {
            [self hideProgressView];
            NSLog(@"Upload Mission Failed");
        }
    }
}

-(void) groundStation:(id<DJIGroundStation>)gs didUploadWaypointMissionWithProgress:(uint8_t)progress
{
    if (self.uploadProgressView == nil) {
        self.uploadProgressView = [[UIAlertView alloc] initWithTitle:@"Mission Uploading" message:@"" delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
        [self.uploadProgressView show];
    }
    
    NSString* message = [NSString stringWithFormat:@"%d%%", progress];
    [self.uploadProgressView setMessage:message];
}

#pragma mark - DJIWaypointConfigViewControllerDelegate Methods

- (void)cancelBtnActionInDJIWaypointConfigViewController:(DJIWaypointConfigViewController *)waypointConfigVC
{
    __weak DJIRootViewController *weakSelf = self;
    
    [UIView animateWithDuration:0.25 animations:^{
        weakSelf.waypointConfigVC.view.alpha = 0;
    }];
    
}

- (void)finishBtnActionInDJIWaypointConfigViewController:(DJIWaypointConfigViewController *)waypointConfigVC
{
    __weak DJIRootViewController *weakSelf = self;
    
    [UIView animateWithDuration:0.25 animations:^{
        weakSelf.waypointConfigVC.view.alpha = 0;
    }];
    
    for (int i = 0; i < self.waypointMission.waypointCount; i++) {
        DJIWaypoint* waypoint = [self.waypointMission waypointAtIndex:i];
        waypoint.altitude = [self.waypointConfigVC.altitudeTextField.text floatValue];
    }
    
    self.waypointMission.maxFlightSpeed = [self.waypointConfigVC.maxFlightSpeedTextField.text floatValue];
    self.waypointMission.autoFlightSpeed = [self.waypointConfigVC.autoFlightSpeedTextField.text floatValue];
    self.waypointMission.headingMode = (DJIWaypointMissionHeadingMode)self.waypointConfigVC.headingSegmentedControl.selectedSegmentIndex;
    self.waypointMission.finishedAction = (DJIWaypointMissionFinishedAction)self.waypointConfigVC.actionSegmentedControl.selectedSegmentIndex;
    
    if (self.waypointMission.isValid) {
    
        if (weakSelf.uploadProgressView == nil) {
            weakSelf.uploadProgressView = [[UIAlertView alloc] initWithTitle:@"" message:@"" delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
            [weakSelf.uploadProgressView show];
        }

        [self.waypointMission setUploadProgressHandler:^(uint8_t progress) {
            
            [weakSelf.uploadProgressView setTitle:@"Mission Uploading"];
            NSString* message = [NSString stringWithFormat:@"%d%%", progress];
            [weakSelf.uploadProgressView setMessage:message];
            
        }];

        [self.waypointMission uploadMissionWithResult:^(DJIError *error) {

            [weakSelf.uploadProgressView setTitle:@"Mission Upload Finished"];

            if (error.errorCode != ERR_Succeeded) {
                [weakSelf.uploadProgressView setMessage:@"Mission Invalid!"];
            }
            
            [weakSelf.waypointMission setUploadProgressHandler:nil];
            [weakSelf performSelector:@selector(hideProgressView) withObject:nil afterDelay:3.0];
            
            [weakSelf.waypointMission startMissionWithResult:^(DJIError *error) {
                if (error.errorCode != ERR_Succeeded) {
                    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Start Mission Failed" message:error.errorDescription delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
                    [alertView show];
                }
            }];
            
        }];

    }else
    {
        UIAlertView *invalidMissionAlert = [[UIAlertView alloc] initWithTitle:@"Waypoint mission invalid" message:@"" delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
        [invalidMissionAlert show];
    }
    
}

#pragma mark - DJIGSButtonViewController Delegate Methods

- (void)stopBtnActionInGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    [self.waypointMission stopMissionWithResult:^(DJIError *error) {
        
        if (error.errorCode == ERR_Succeeded) {
            UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Stop Mission Success" message:@"" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alertView show];
        }

    }];

}

- (void)clearBtnActionInGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    [self.mapController cleanAllPointsWithMapView:self.mapView];
}

- (void)focusMapBtnActionInGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    [self focusMap];
}

- (void)configBtnActionInGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    __weak DJIRootViewController *weakSelf = self;
    
    NSArray* wayPoints = self.mapController.wayPoints;
    if (wayPoints == nil || wayPoints.count < DJIWaypointMissionMinimumWaypointCount) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"No or not enough waypoint for mission" message:@"" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        return;
    }
    
    [UIView animateWithDuration:0.25 animations:^{
        weakSelf.waypointConfigVC.view.alpha = 1.0;
    }];
    
    [self.waypointMission removeAllWaypoints];

    for (int i = 0; i < wayPoints.count; i++) {
        CLLocation* location = [wayPoints objectAtIndex:i];
        if (CLLocationCoordinate2DIsValid(location.coordinate)) {
            DJIWaypoint* waypoint = [[DJIWaypoint alloc] initWithCoordinate:location.coordinate];
            [self.waypointMission addWaypoint:waypoint];
        }
    }
    
}

- (void)startBtnActionInGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    [self.waypointMission startMissionWithResult:^(DJIError *error) {
        if (error.errorCode != ERR_Succeeded) {
            UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Start Mission Failed" message:error.errorDescription delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alertView show];
        }
    }];
}

- (void)switchToMode:(DJIGSViewMode)mode inGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    if (mode == DJIGSViewMode_EditMode) {
        [self focusMap];
    }
    
}

- (void)addBtn:(UIButton *)button withActionInGSButtonVC:(DJIGSButtonViewController *)GSBtnVC
{
    if (self.isEditingPoints) {
        self.isEditingPoints = NO;
        [button setTitle:@"Add" forState:UIControlStateNormal];
    }else
    {
        self.isEditingPoints = YES;
        [button setTitle:@"Finished" forState:UIControlStateNormal];
    }
}

#pragma mark - CLLocationManagerDelegate
- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
{
    CLLocation* location = [locations lastObject];
    self.userLocation = location.coordinate;
}

#pragma mark MKMapViewDelegate Method
- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation
{
    if ([annotation isKindOfClass:[MKPointAnnotation class]]) {
        MKPinAnnotationView* pinView = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"Pin_Annotation"];
        pinView.pinColor = MKPinAnnotationColorPurple;
        return pinView;
        
    }else if ([annotation isKindOfClass:[DJIAircraftAnnotation class]])
    {
        DJIAircraftAnnotationView* annoView = [[DJIAircraftAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"Aircraft_Annotation"];
        ((DJIAircraftAnnotation*)annotation).annotationView = annoView;
        return annoView;
    }
    
    return nil;
}

- (void)enterNavigationMode
{
    [self.navigationManager enterNavigationModeWithResult:^(DJIError *error) {
        if (error.errorCode != ERR_Succeeded) {
            NSString* message = [NSString stringWithFormat:@"Enter navigation mode failed:%@", error.errorDescription];
            UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Enter Navigation Mode" message:message delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Retry", nil];
            alertView.tag = kEnterNaviModeFailedAlertTag;
            [alertView show];
        }else
        {
            NSString* message = @"Enter navigation mode Success";
            UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Enter Navigation Mode" message:message delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alertView show];
            
        }
    }];
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView.tag == kEnterNaviModeFailedAlertTag) {
        if (buttonIndex == 1) {
            [self enterNavigationMode];
        }
    }
}

#pragma mark - DJIDroneDelegate Method
-(void) droneOnConnectionStatusChanged:(DJIConnectionStatus)status
{
    if (status == ConnectionSucceeded) {
        [self enterNavigationMode];
    }
}

#pragma mark - DJIMainControllerDelegate Method

-(void) mainController:(DJIMainController*)mc didUpdateSystemState:(DJIMCSystemState*)state
{
    self.droneLocation = state.droneLocation;
    
    if (!state.isMultipleFlightModeOpen) {
        [self.inspireMainController setMultipleFlightModeOpen:YES withResult:nil];
    }
    
    self.modeLabel.text = state.flightModeString;
    self.gpsLabel.text = [NSString stringWithFormat:@"%d", state.satelliteCount];
    self.vsLabel.text = [NSString stringWithFormat:@"%0.1f M/S",state.velocityZ];
    self.hsLabel.text = [NSString stringWithFormat:@"%0.1f M/S",(sqrtf(state.velocityX*state.velocityX + state.velocityY*state.velocityY))];
    self.altitudeLabel.text = [NSString stringWithFormat:@"%0.1f M",state.altitude];
    
    [self.mapController updateAircraftLocation:self.droneLocation withMapView:self.mapView];
    double radianYaw = (state.attitude.yaw * M_PI / 180.0);
    [self.mapController updateAircraftHeading:radianYaw];
    
}

@end