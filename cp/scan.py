from tweepy.streaming import StreamListener
from tweepy import Stream
import tweepy, time, signal, termios, struct, fcntl, sys, readline
import settings, auth

__author__ = 'Josh Johnson, Riley Hirn'

#count of tweets
count = 0

def main():
    print "\n"
    for i in range(3, 0, -1):
    	print "\033[7mStarting script in %d seconds...\033[0m" % (i,)
    	time.sleep(1)
    	blank_current_readline()

    signal.signal(signal.SIGINT, interruptHandler)

    #twitter authorization
    authorization = tweepy.OAuthHandler(auth.cKey, auth.cSecret)
    authorization.set_access_token(auth.aToken, auth.aSecret)

    api = tweepy.API(authorization)

    listener = TweetListener()

    blank_current_readline()
    print chr(27) + "[2J"

    stream = Stream(authorization, listener)
    print 'Now scanning for #' + settings.hashtag + '...\n\n'

    stream.filter(track=['#' + settings.hashtag])


# Listener to handle discovered tweets
class TweetListener(StreamListener):

	# Tweet found with given hashtag
	def on_status(self, status):
		blank_current_readline()
		blank_current_readline()
		blank_current_readline()

		print 'Tweet: ' + status.text.encode('utf-8')
		print 'Tweet Author: @' + status.user.screen_name

		print '\n'

		global count
		count += 1
		print "\033[32m-----------------------\033[0m"
		print "\033[7mTweets scanned: %d\033[0m" % (count,)
		print "\033[32m-----------------------\033[0m"

	def on_error(self, status_code):
		print '\033[22;31mTweet error: \033[4;31m' + str(status_code) + '\033[0m'
		if status_code == 420:
			reconnect(10)
		else:
			reconnect(3)
		return True

	def on_timeout(self):
		print('\033[22;31mTimeout...\033[0m')
		reconnect(3)
		return True


#############
# functions #
#############

# Print method for debug mode
def debug_print(text):
	if settings.debug:
		print "\033[0m\033[22;36m" + text.encode('utf-8') + '\033[0m'

# Parse the tweet for selection and handle it accordingly
def sendTweet(tweet):
    print "Sending."

def reconnect(wait):

		for i in range(wait, 0, -1):
			print "Reconnecting in %d seconds..." % (i,)
			time.sleep(1)
			blank_current_readline()

		print 'Reconnecting...'

		auth = tweepy.OAuthHandler(settings.cKey, settings.cSecret)
		auth.set_access_token(settings.aToken, settings.aSecret)

		api = tweepy.API(auth)
		listener = TweetListener()

		debug_print('\nStarting stream for #%s...' % (settings.hashtag1,))

		stream = Stream(auth, listener)
		print 'Now scanning for #' + settings.hashtag1 + '...'

		stream.filter(track=['#' + settings.hashtag1])

def blank_current_readline():
	# Next line said to be reasonably portable for various Unixes
	(rows,cols) = struct.unpack('hh', fcntl.ioctl(sys.stdout, termios.TIOCGWINSZ,'1234'))

	text_len = len(readline.get_line_buffer())+2

	# ANSI escape sequences (All VT100 except ESC[0G)
	sys.stdout.write('\x1b[1A')                         # Move cursor up
	sys.stdout.write('\x1b[0G')                         # Move to start of line
	sys.stdout.write('\x1b[2K')                         # Clear current line


def interruptHandler(signal, frame):
	print '\n\033[31mExiting...\033[0m'
	sys.exit(0)

if __name__ == "__main__":
    main()
