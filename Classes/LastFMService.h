/* LastFMService.h - AudioScrobbler webservice proxy
 * 
 * Copyright 2009 Last.fm Ltd.
 *   - Primarily authored by Sam Steele <sam@last.fm>
 *
 * This file is part of MobileLastFM.
 *
 * MobileLastFM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MobileLastFM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MobileLastFM.  If not, see <http://www.gnu.org/licenses/>.
 */

#import <Foundation/Foundation.h>
#import "CXMLDocument.h"
#import "apikey.h"

#define LastFMServiceErrorDomain @"LastFMServiceErrorDomain"

enum serviceErrorCodes {
	errorCodeInvalidService = 2,
	errorCodeInvalidMethod = 3,
	errorCodeAuthenticationFailed = 4,
	errorCodeInvalidFormat = 5,
	errorCodeInvalidParameters = 6,
	errorCodeInvalidResource = 7,
	errorCodeOperationFailed = 8,
	errorCodeInvalidSession = 9,
	errorCodeInvalidAPIKey = 10,
	errorCodeServiceOffline = 11,
	errorCodeSubscribersOnly = 12,
	errorCodeInvalidAPISignature = 13
};

enum radioErrorCodes {
	errorCodeNotEnoughContent = 20,
	errorCodeNotEnoughMembers = 21,
	errorCodeNotEnoughFans = 22,
	errorCodeNotEnoughNeighbours = 23
};

enum eventStatus {
	eventStatusAttending = 0,
	eventStatusMaybeAttending = 1,
	eventStatusNotAttending = 2 
};

@interface LastFMService : NSObject {
	NSString *session;
	NSError *error;
}
@property (nonatomic, retain) NSString *session;
@property (readonly) NSError *error;

+ (LastFMService *)sharedInstance;
- (NSArray *)doMethod:(NSString *)method maxCacheAge:(double)seconds XPath:(NSString *)XPath withParameters:(NSString *)firstParam, ...;

#pragma mark Artist methods

- (NSDictionary *)metadataForArtist:(NSString *)artist inLanguage:(NSString *)lang;
- (NSArray *)eventsForArtist:(NSString *)artist;
- (NSArray *)artistsSimilarTo:(NSString *)artist;
- (NSArray *)searchForArtist:(NSString *)artist;
- (NSArray *)topTagsForArtist:(NSString *)artist;
- (void)addTags:(NSArray *)tags toArtist:(NSString *)artist;
- (void)removeTag:(NSString *)tag fromArtist:(NSString *)artist;
- (NSArray *)tagsForArtist:(NSString *)artist;

#pragma mark Album methods

- (NSDictionary *)metadataForAlbum:(NSString *)album byArtist:(NSString *)artist inLanguage:(NSString *)lang;
- (NSArray *)topTagsForAlbum:(NSString *)track byArtist:(NSString *)artist;
- (void)addTags:(NSArray *)tags toAlbum:(NSString *)album byArtist:(NSString *)artist;
- (void)removeTag:(NSString *)tag fromAlbum:(NSString *)album byArtist:(NSString *)artist;
- (NSArray *)tagsForAlbum:(NSString *)album byArtist:(NSString *)artist;

#pragma mark Track methods

- (void)loveTrack:(NSString *)title byArtist:(NSString *)artist;
- (void)banTrack:(NSString *)title byArtist:(NSString *)artist;
- (NSArray *)fansOfTrack:(NSString *)track byArtist:(NSString *)artist;
- (NSArray *)topTagsForTrack:(NSString *)track byArtist:(NSString *)artist;
- (void)recommendTrack:(NSString *)track byArtist:(NSString *)artist toEmailAddress:(NSString *)emailAddress;
- (void)addTags:(NSArray *)tags toTrack:(NSString *)track byArtist:(NSString *)artist;
- (void)removeTag:(NSString *)tag fromTrack:(NSString *)track byArtist:(NSString *)artist;
- (NSArray *)tagsForTrack:(NSString *)track byArtist:(NSString *)artist;

#pragma mark User methods

- (void)createUser:(NSString *)username withPassword:(NSString *)password andEmail:(NSString *)email;
- (NSDictionary *)getMobileSessionForUser:(NSString *)username password:(NSString *)password;
- (NSArray *)friendsOfUser:(NSString *)username;
- (NSArray *)topArtistsForUser:(NSString *)username;
- (NSArray *)topAlbumsForUser:(NSString *)username;
- (NSArray *)topTracksForUser:(NSString *)username;
- (NSArray *)tagsForUser:(NSString *)username;
- (NSArray *)recentlyPlayedTracksForUser:(NSString *)username;
- (NSArray *)playlistsForUser:(NSString *)username;
- (NSArray *)eventsForUser:(NSString *)username;
- (NSArray *)recommendedEventsForUser:(NSString *)username;
- (NSDictionary *)profileForUser:(NSString *)username;
- (NSDictionary *)compareArtistsOfUser:(NSString *)username withUser:(NSString *)username2;
- (NSArray *)recentStationsForUser:(NSString *)username;

#pragma mark Tag methods

- (NSArray *)tagsSimilarTo:(NSString *)tag;
- (NSArray *)searchForTag:(NSString *)tag;
- (NSArray *)topArtistsForTag:(NSString *)tag;

#pragma mark Radio methods

- (NSDictionary *)tuneRadioStation:(NSString *)stationURL;
- (NSDictionary *)getPlaylist;

#pragma mark Event methods

- (void)attendEvent:(int)event status:(int)status;
- (NSArray *)eventsForLatitude:(float)latitude longitude:(float)longitude radius:(int)radius;

#pragma mark Playlist methods

- (void)addTrack:(NSString *)track byArtist:(NSString *)artist toPlaylist:(int)playlist;
- (NSDictionary *)createPlaylist:(NSString *)title;

@end