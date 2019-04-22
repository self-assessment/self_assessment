<?php

class SelfAssessmentAdminOverview {
    public static function index() {
        /**
        * Admin page for feedback settings.
        */
        $rows = [];
        $header = [
            t('Title'),
            t('Author'),
            t('Updated'),
            t('Operations'),
        ];

        foreach (self::list() as $key => $time) {
            $operations = [
                l(t('edit'), "node/$key/edit"),
                l(t('delete'), "node/$key/delete"),
            ];
            $rows[] = [
                l($time['title'], "node/$key"),
                $time['name'],
                format_date($time['changed']),
                implode(' ', $operations),
            ];
        }

        $table = theme(
            'table',
            [
                'caption' => t('Quiz feedback conditions'),
                'rows' => $rows,
                'header' => $header
            ]
        );

        $menu = '';
        $item = menu_get_item();
        if ($content = system_admin_menu_block($item)) {
            $menu = theme('admin_block_content', array(
              'content' => $content,
            ));
        }

        return $menu.$table;
    }

    protected static function list() {
        $results = [];
        $args = [];

        $query = db_select('node', 'n')
            ->fields('n', array('nid', 'vid', 'title', 'uid', 'changed'))
            ->fields('u', array('name'));

        $query->leftJoin('users', 'u', 'u.uid = n.uid');
        $query->leftJoin('quiz_node_properties', 'np', 'np.nid = n.nid');
        $query->condition('n.type', 'quiz');
        $query->condition('np.self_assessment', true);
        $query->orderBy('n.nid');
        $quizzes = $query->execute();

        foreach ($quizzes as $quiz) {
            $results[$quiz->nid] = (array) $quiz;
        }

        return $results;
    }
}
