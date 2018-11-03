#! /usr/bin/perl -w
use Glib qw/TRUE FALSE/;
use Gtk2 '-init';

# ------------------------------------------------------------------------
#  Display a 300x120 pixel window with a title, two buttons (Status, Quit)
#     and a status message
#  if the user clicks the status button, an updated status is displayed
#  if the user clicks the quit button, the window and program close
#  if the user clicks the x in the upper right corner,
#     a pop-up dialog is generated asking if they really want to quit
#  various reports are also printed to the console during execution
# ------------------------------------------------------------------------

# handler function to respond to clicking the Quit button
#   - the implicit first parameter is the widget that caused the event,
#   - the remaining parameters are determined by how the signal_connect was set
#     up to call the handler
# in this case the second parameter is a reference to the window the button is in
sub handle_quit ($$)
{
   my $widget = $_[0];
   my $window = $_[1];
   # print a message
   print "Goodbye!\n";
   # destroy the associated window
   $window->destroy;
}

# handler function to respond to clicking the Status button,
#   - the parameters are for the status button and the label to write the status in
# in this case the second parameter is a reference to the window the button is in
sub handle_status ($$)
{
   my $widget = $_[0];
   my $label = $_[1];
   $label->set_text("status updated");
   print "tried status update\n";
   return FALSE;
}

# our handler to respond to an attempt to closing the main window via the X,
#     writes a premature-close message to the console then closes window
sub handle_delete($)
{
   my $window = $_[0];
   # right now our handling will just print a message
   print "user tried to close window using the upper-right-x\n";

   # run a popup to see if they really wanted to quit
   my $ans = display_dialog($window, 'quit now, really?');
   if ($ans == 1) {
      print "   ...confirmed window destruction\n";
      $window->destroy;
      return FALSE; # we've killed it
   } else {
      print "   ...rejected window destruction\n";
      return TRUE; # we're not killing it after all
   }
}

# shutdown the program in response to a destroy call on the main window
#    (could come from handle_quit or from handle_destroy)
sub shutdown($)
{
   Gtk2->main_quit;
}

# function to display a dialog message,
#    assumes first parameter is main window, second is the message
sub display_dialog($$)
{
   my $window = $_[0];
   my $message = $_[1];
   my $dialog = Gtk2::MessageDialog->new($window, 'destroy-with-parent',
        'question', 'yes-no', $message);
   my $response = $dialog->run;
   if ($response eq 'yes') {
      $response = 1;
   } else {
      $response = 0;
   }
   $dialog->destroy;
   return $response;
}

# ----------------------------------------------------------------------
# main routine: define the window elements, display them,
#    and start the event loop
# ----------------------------------------------------------------------

sub main()
{
   # (1) create the main window with boxes holding the label and quit, status buttons
   # --------------------------------------------------------------------------------
   # create the main window with border width 10 and title 265 expt
   my $mainWindow = Gtk2::Window->new("toplevel");
   $mainWindow->set_border_width(10);
   $mainWindow->set_title('265 expt');
   $mainWindow->set_size_request(300,120);

   # a v-box will hold two rows,
   #   one row is just the status message,
   #   the other is an h-box containing two buttons (quit and status)

   # create the vbox to hold the two rows, add it to the main window
   my $vbox = Gtk2::VBox->new(TRUE, 2);
   $mainWindow->add($vbox);

   # create the hbox to hold the two buttons, and add it to the vbox
   my $hbox = Gtk2::HBox->new(TRUE, 2);
   $vbox->pack_start($hbox, TRUE, TRUE, 1);

   # create a button labelled Status and pack it into the hbox
   my $statusButton = Gtk2::Button->new("Status");
   $hbox->pack_start($statusButton, TRUE, TRUE, 0);

   # create a button labelled Quit and pack it into the hbox
   my $quitButton = Gtk2::Button->new("Quit");
   $hbox->pack_start($quitButton, TRUE, TRUE, 0);

   # create a label (currently "status unknown") and pack it into the vbox
   my $statusLabel = Gtk2::Label->new("status unknown");
   $vbox->pack_start($statusLabel, TRUE, TRUE, 0);

   # (2) connect the event handlers to the window and buttons
   # --------------------------------------------------------
   # connect the window to the delete_event signal,
   #    and use function delete_event to handle it
   # (signal connect links known event types to handler functions, passed by ref)
   $mainWindow->signal_connect( delete_event => \&handle_delete );

   # connect the window to the destroy event, in which we shut down the program
   #    (could be invoked from either the handler for quit or for delete)
   $mainWindow->signal_connect( destroy => \&shutdown);

   # connect the statusButton to the clicked event, with our "handle_status" function as handler,
   #    passing the window's label as a parameter so its content can be changed
   $statusButton->signal_connect( clicked => \&handle_status, $statusLabel);

   # connect the quitButton to the clicked event, with our "handle_quit" function as its handler,
   #    passing the button's window as a parameter
   $quitButton->signal_connect( clicked => \&handle_quit, $mainWindow);

   # (3) display the window and buttons
   # ----------------------------------
   # display the buttons and labels, then the boxes, then the main window
   # (show from the inside out, so user doesn't see elements pop up one by one)
   $statusButton->show;
   $quitButton->show;
   $statusLabel->show;
   $hbox->show;
   $vbox->show;
   $mainWindow->show;

   # (4) start the event handler
   # ---------------------------
   # start the beastie running, gtk's main routine
   #    listens for events and propagates them to the correct handler
   Gtk2->main;
}

# invoke the main routine, quit when it finishes
main();

0;

