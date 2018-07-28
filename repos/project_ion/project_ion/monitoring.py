import logging
from watchdog.events import PatternMatchingEventHandler


class FileMonitoringEventHandler(PatternMatchingEventHandler):
    def on_created(self, event):
        """ Parse and create object in DB """
        super(FileMonitoringEventHandler, self).on_created(event)

        what = 'directory' if event.is_directory else 'file'
        logging.info("Created %s: %s", what, event.src_path)

    def on_modified(self, event):
        """ Reparse and update DB """
        super(FileMonitoringEventHandler, self).on_modified(event)

        what = 'directory' if event.is_directory else 'file'
        logging.info("Modified %s: %s", what, event.src_path)

    def on_moved(self, event):
        """ Update Path in DB"""
        super(FileMonitoringEventHandler, self).on_moved(event)

        what = 'directory' if event.is_directory else 'file'
        logging.info("Moved %s: from %s to %s", what, event.src_path,
                     event.dest_path)

    def on_deleted(self, event):
        """ Remove from DB """
        super(FileMonitoringEventHandler, self).on_deleted(event)

        what = 'directory' if event.is_directory else 'file'
        logging.info("Deleted %s: %s", what, event.src_path)
